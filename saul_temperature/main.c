#include <stdio.h>
#include <saul.h>

int main(void) {
    int *dev = saul_init_devs();  // Initialize the SAUL module

    phydat_t result;  // Create a variable to store the sensor data

    int sensor_status = saul_read_notsup(dev, &result);  // Read data from the sensor

    if (sensor_status == 0) {
        printf("Sensor data: %d\n", result.val[0]);  // Print the sensor data
    } else {
        printf("Failed to read sensor data\n");
    }

    return 0;
}
