//client to recieve published message
 
import paho.mqtt.client as mqtt

# MQTT broker details
broker_address = "ipv6:address::" //need to put ipv6 address where broker running
broker_port = 1886 //mqttsn listening port
topic = "sensor/temperature"

# Callback function for when a connection is established with the MQTT broker
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker")
    # Subscribe to the topic upon successful connection
    client.subscribe(topic)

# Callback function for when a message is received
def on_message(client, userdata, message):
    print("Received message: " + str(message.payload.decode()))

# Create MQTT client instance
client = mqtt.Client()

# Set callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to MQTT broker
client.connect(broker_address, broker_port)

# Start the network loop to listen for incoming messages periodically
client.loop_forever()

