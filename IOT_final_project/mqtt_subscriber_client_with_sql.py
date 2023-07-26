import paho.mqtt.client as mqtt
import mysql.connector

client_id = "subscriber_client_with_sql"

# MQTT broker details
broker_address = "2600:1f18:6929:5505:5ea4:f15c:41fb:1872"
broker_port = 1886
topic = "sensor/temperature"

# MySQL database details
db_host = "localhost"
db_user = "root"
db_password = "admin"
db_name = "TemperatureReadings"

# Function when a connection is established with the MQTT broker
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker")
    # Subscribe to the topic upon successful connection
    client.subscribe(topic)

# Function when a message is received
def on_message(client, userdata, message):
    print("Received message: " + str(message.payload.decode()))

    # Insert the received temperature into the database
    try:
        connection = mysql.connector.connect(
            host=db_host,
            user=db_user,
            password=db_password,
            database=db_name
        )

        cursor = connection.cursor()

        # Extract the temperature value from the received message
        payload = str(message.payload.decode())

        # Extract the numeric part after the colon
        temperature = payload.split(":")[1].strip()

        # Prepare the SQL query to insert the temperature reading
        insert_query = "INSERT INTO `Readings` (`datetime`, `temperature`) VALUES (NOW(), %s)"
        data = (temperature,)

        # Execute the query
        cursor.execute(insert_query, data)

        # Commit the changes to the database
        connection.commit()

        print("Temperature reading saved successfully!")

    except mysql.connector.Error as error:
        print("Error while connecting to MySQL:", error)

    finally:
        # Close the database connection
        if connection.is_connected():
            cursor.close()
            connection.close()

# Create MQTT client instance
client = mqtt.Client(client_id=client_id, clean_session=True)

# Set callback functions
client.on_connect = on_connect
client.on_message = on_message

# Connect to MQTT broker
client.connect(broker_address, broker_port)

# Start the network loop to listen for incoming messages
client.loop_forever()
