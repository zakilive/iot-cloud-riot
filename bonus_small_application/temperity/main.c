
// Syed Ahmed Zaki - HIS Project-Group 4, Frankfurt University of Âpplied Science
// This below code work with nrf2840dk boards pin P0.03(A0)
// Some of the logic referred from riot os tests/dht

#include <stdio.h>
#include "xtimer.h"
#include "timex.h"
#include "fmt.h"
#include "dht.h"

#include "clk.h"
#include "board.h"
#include "periph_conf.h"
#include "timex.h"
#include "ztimer.h"
#include "periph/gpio.h"
//all headers included

#define DELAY           (2 * US_PER_SEC)

int main(void)
{
    dht_t dev1;
    dht_params_t my_params;
    int16_t temp, hum;

    my_params.pin = GPIO_PIN(0,3);
    my_params.type=DHT11;

    puts("DHT temperature and humidity sensor application\n");

    /* initialize first configured sensor */
    printf("Initialization status of DHT sensor...\t");
    if (dht_init(&dev1, &my_params) == DHT_OK) {
        puts("[Connected]\n");
    }
    else {
        puts("[Connection Fails]");
        return 1;
    }

    /* periodically read temperature and humidity values */
    while (1) {
        if (dht_read(&dev1, &temp, &hum) != DHT_OK) {
            puts("Error reading values");
            continue;
        }

        printf("DHT values - temperature: %d.%d°C - relative humidity: %d.%d%%\n",
               temp/10, temp%10, hum/10, hum%10);

        xtimer_usleep(DELAY);
    }

    return 0;
}
