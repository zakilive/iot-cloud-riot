# temperity
temperity is a RIOT application to check temperature and humidity with dht sensors

#install
download whole temperity folder and put inside the tests directory of riot-os
then use below line to flash for ACM0 serial port,
BOARD=nrf52840dk PORT=/dev/ttyACM0 make term flash

#output
Something like below will be shown:
2023-06-04 15:27:33,327 # Error reading values
2023-06-04 15:27:33,342 # DHT values - temp: 30.0°C - relative humidity: 10.0%
2023-06-04 15:27:35,344 # DHT values - temp: 30.0°C - relative humidity: 10.0%
2023-06-04 15:27:37,374 # Error reading values
2023-06-04 15:27:37,437 # Error reading values
2023-06-04 15:27:37,510 # Error reading values
