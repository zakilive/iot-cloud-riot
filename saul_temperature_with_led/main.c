#include <stdio.h>
#include <saul.h>
#include"saul_reg.h"

#include "clk.h"
#include "board.h"
#include "periph_conf.h"
#include "timex.h"
#include "ztimer.h"
#include "periph/gpio.h"

#define ON 1
#define OFF 0

static void delay(void)
{
    if (IS_USED(MODULE_ZTIMER)) {
        ztimer_sleep(ZTIMER_USEC, 1 * US_PER_SEC);
    }
    else {
        uint32_t loops = coreclk() / 20;
        for (volatile uint32_t i = 0; i < loops; i++) { }
    }
}

static void print_led(void) {
    gpio_init(GPIO_PIN(0,3),GPIO_OUT);

   	gpio_write(GPIO_PIN(0,3),ON);
	delay();
	gpio_write(GPIO_PIN(0,3),OFF);

}

static void temp_saul(void) {
    int sensor_status;

   	saul_reg_t *dev = saul_reg_find_nth(8);
	phydat_t result;

    sensor_status=saul_reg_read(dev, &result);
    puts("Sensor Status");

    while(1) {
        if (sensor_status >= 0) {
            int temperature_celsius=result.val[0]/100;
            printf("Sensor data: %d\n", temperature_celsius);  // Print the sensor data
            if (temperature_celsius>29) {
                print_led();
            }

        } else {
            printf("Failed to read sensor data\n");
        }
    }
}

int main(void) {
	temp_saul();

    return 0;
}
