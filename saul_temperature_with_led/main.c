#include <stdio.h>
#include "dht.h"
#include "saul_reg.h"
#include "saul.h"

#include "time_units.h"
#include "ztimer.h"

#include "periph/gpio.h"
#include "periph_conf.h"

#define ON 1
#define OFF 0

static void _print_led(void) {
	gpio_init(GPIO_PIN(0,4),GPIO_OUT);

   	gpio_write(GPIO_PIN(0,4),ON);
	ztimer_sleep(ZTIMER_SEC, 1); //need timer for delay
	gpio_write(GPIO_PIN(0,4),OFF);
	ztimer_sleep(ZTIMER_SEC, 1); //need timer for delay
}

static void _dht_func(void) {
	static saul_reg_t *saul_dht;
	static phydat_t result;
	saul_dht = saul_reg_find_name("dht");

		
	
	while(1) {
		int res = saul_reg_read(saul_dht, &result); //need to put it in while loop to get data sequencially
		int temp_val = result.val[0]/10;
	
		if (res) {
			printf("temperature: %d C\n", temp_val); //newline \n is needful to print it
			if (temp_val > 23) { //if environment temperature is greater than 23 light will blink
				_print_led();
			}
		} else {
			printf("Sensor read failure: %d\n", res);
		}		
		
		ztimer_sleep(ZTIMER_USEC, 5); //need timer for delay
	}
}

int main(void)
{
	_dht_func();

	return 0;
}
