#include <stdio.h>
#include <saul.h>
#include"saul_reg.h"


static void temp_saul(void) {
    int sensor_status;

   	saul_reg_t *dev = saul_reg_find_nth(8);
	phydat_t result;

    sensor_status=saul_reg_read(dev, &result);
    puts("Sensor Status");
    
    while(1) {
        if (sensor_status >= 0) {
            printf("Sensor data: %d\n", result.val[0]/100);  // Print the sensor data from nRF52840 board
        } else {
            printf("Failed to read sensor data\n");
        }
    }
}

int main(void) {
	temp_saul();

    return 0;
}
