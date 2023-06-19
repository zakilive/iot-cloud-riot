#include <stdio.h>
#include <saul.h>
#include"saul_reg.h"

int main(void) {
    // int *dev = saul_init_devs();  // Initialize the SAUL module
    //
    // phydat_t result;  // Create a variable to store the sensor data
    //
    // int sensor_status = saul_read_notsup(dev, &result);  // Read data from the sensor
    //
    // if (sensor_status == 0) {
    //     printf("Sensor data: %d\n", result.val[0]);  // Print the sensor data
    // } else {
    //     printf("Failed to read sensor data\n");
    // }

    int sensor_status;

   	saul_reg_t *dev = saul_reg_find_nth(8);
	phydat_t result;

    sensor_status=saul_reg_read(dev, &result);
    puts("Sensor Status");
    
    while(1) {
        if (sensor_status >= 0) {
            printf("Sensor data: %d, %d\n", result.val[0], result.scale);  // Print the sensor data
        } else {
            printf("Failed to read sensor data\n");
        }
    }

    


//    return sensor_status;

    return 0;
}
