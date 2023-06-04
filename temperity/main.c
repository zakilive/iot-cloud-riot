// Syed Ahmed Zaki - HIS Project-Group 4, Frankfurt University of Âpplied Science
#include <stdio.h>
#include "xtimer.h"
#include "timex.h"
#include "fmt.h"
#include "dht.h"
#include "dht_params.h"
#include "clk.h"
#include "board.h"
#include "periph_conf.h"
#include "timex.h"
#include "ztimer.h"
#include "periph/gpio.h"

#define DELAY           (1 * US_PER_SEC)

int main(void)
{
    dht_t dev1;
    dht_params_t my_params;
    int16_t temp, hum;

    my_params.pin = GPIO_PIN(0,3);

    puts("DHT temperature and humidity sensor test application\n");
    // dht_params_t dht_type;
    // gpio_init(GPIO_PIN(0,3),GPIO_IN);
    // gpio_read(3);

    /* initialize first configured sensor */
    printf("Initializing DHT sensor...\t");
    if (dht_init(&dev1, &my_params) == DHT_OK) {
        puts("[OK]\n");
    }
    else {
        puts("[Failed]");
        return 1;
    }

    /* periodically read temperature and humidity values */
    while (1) {
        if (dht_read(&dev1, &temp, &hum) != DHT_OK) {
            puts("Error reading values");
            continue;
        }

        printf("DHT values - temp: %d.%d°C - relative humidity: %d.%d%%\n",
               temp/10, temp%10, hum/10, hum%10);

        xtimer_usleep(DELAY);
    }

    return 0;
}
