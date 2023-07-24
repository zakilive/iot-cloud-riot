#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"
#include "msg.h"

#include "net/emcute.h"
#include "net/ipv6/addr.h"
#include "thread.h"

#include "dht.h"
#include "saul_reg.h"
#include "saul.h"

#include <time.h>
#include "time_units.h"
#include "ztimer.h"

#include "periph/gpio.h"
#include "periph_conf.h"

#define ON 1
#define OFF 0

//Using emcute_mqttsn package
//ref: https://github.com/RIOT-OS/RIOT/tree/master/examples/emcute_mqttsn
#ifndef EMCUTE_ID
#define EMCUTE_ID           ("gertrud")
#endif
#define EMCUTE_PRIO         (THREAD_PRIORITY_MAIN - 1)

#define NUMOFSUBS           (16U)
#define TOPIC_MAXLEN        (64U)

static char stack[THREAD_STACKSIZE_DEFAULT];
static msg_t queue[8];

static emcute_sub_t subscriptions[NUMOFSUBS];

static void *emcute_thread(void *arg)
{
    (void)arg;
    emcute_run(CONFIG_EMCUTE_DEFAULT_PORT, EMCUTE_ID);
    return NULL;    /* should never be reached */
}

// Function to connect to the broker
static int connect(char *address, int port)
{
    sock_udp_ep_t gw = { .family = AF_INET6, .port = CONFIG_EMCUTE_DEFAULT_PORT };
    gw.port=port;

    /* parse address */
    if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, address) == NULL) {
        printf("error parsing IPv6 address\n");
        return 1;
    }

    if (emcute_con(&gw, true, NULL, NULL, 0, 0) != EMCUTE_OK) {
        printf("error: unable to connect to [%s]:%i\n", address, port);
        return 1;
    }

    printf("Successfully connected to gateway at [%s]:%i\n", address, port);

    return 0;
}


// Function to disconnect from MQTT-SN gateway
static int disconnect(void)
{
    int res = emcute_discon();

    if (res == EMCUTE_NOGW) {
        puts("error: not connected to any broker");
        return 1;
    }
    else if (res != EMCUTE_OK) {
        puts("error: unable to disconnect");
        return 1;
    }
    puts("Disconnect successful");
    return 0;
}

// Function to publish messages
static int publish(char* topic, char *data, int qos)
{
    emcute_topic_t t;
    unsigned flags = EMCUTE_QOS_0;

    /* parse QoS level */
    switch (qos) {
        case 1:
            flags |= EMCUTE_QOS_1;
            break;
        case 2:
            flags |= EMCUTE_QOS_2;
            break;
        default:
            flags |= EMCUTE_QOS_0;
            break;
    }

    /* step 1: get topic id */
    t.name = topic;
    if (emcute_reg(&t) != EMCUTE_OK) {
        puts("error: unable to obtain topic ID");
        return 1;
    }

    /* step 2: publish data */
    if (emcute_pub(&t, data, strlen(data), flags) != EMCUTE_OK) {
        printf("error: unable to publish data to topic '%s [%i]'\n", t.name, (int)t.id);
        return 1;
    }

    printf("Published %s on topic %s\n",data, topic);

    return 0;
}

// LED light function
static void print_led(void) {
	gpio_init(GPIO_PIN(0,4),GPIO_OUT);

   	gpio_write(GPIO_PIN(0,4),ON);
	ztimer_sleep(ZTIMER_SEC, 1); //need timer for delay
	gpio_write(GPIO_PIN(0,4),OFF);
	ztimer_sleep(ZTIMER_SEC, 1); //need timer for delay
}


// DHT sensor function
static int dht_func(void) {

	static saul_reg_t *saul_dht;
	static phydat_t result;
	saul_dht = saul_reg_find_name("dht");



	while(1) {
		int res = saul_reg_read(saul_dht, &result); //need to put it in while loop to get data periodically
		int temperature_value = result.val[0]/10;

		if (res) {
			if (temperature_value > 23) { //if environment temperature is greater than 23 LED red light will blink
				print_led();
			}
			return temperature_value;
		}
		ztimer_sleep(ZTIMER_USEC, 5); //need this delay for correct data from sensor
	}
	return 0;
}

// Start function of the application
static int start_func(int argc, char **argv){
  if (argc < 3) {
      printf("usage:start <address> <port> \n");
      return 1;
  }

    // topic that will publish
    char topic[32];
    sprintf(topic,"sensor/temperature");

    // message that will publish
    char message[32];

    // it connect to the gateway
    if (connect(argv[1], atoi(argv[2]))) {
	// need to keep it for arguments from commandline
    }
    
    int counter = 0;
    while(counter<5) { // 5 times this loop will publish temperature
        int temperature = dht_func();
        
        // temperature value to send
        sprintf(message, "temperature:%d",temperature);

        // publsh the topic and the message with QoS=0
        publish(topic, message, 0);
        
        // delay of 5 seconds to get data
	ztimer_sleep(ZTIMER_SEC, 5);
	
	//total 5 iteration of sending data
	counter++;
    }

    	//disconnect from gateway after 5 times data send
	disconnect();
	
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "start", "Start the Application", start_func },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("Application for Temperature Monitoring with MQTT-SN and AWS\n");
    puts("Type 'help' to get help with usage");

    /* the main thread needs a msg queue to be able to run `ping`*/
    msg_init_queue(queue, ARRAY_SIZE(queue));

    /* initialize our subscription buffers */
    memset(subscriptions, 0, (NUMOFSUBS * sizeof(emcute_sub_t)));

    /* start the emcute thread */
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0,
                  emcute_thread, NULL, "emcute");

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
