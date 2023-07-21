
# IoT-cloud-riot
Authors: Linta Joseph (1474363), Syed Ahmed Zaki(1322363)

# Architecture
![image](Architecture.jpeg)

# Demonstration 
[Google Drive link to the video]()

# Presentation 
   Presentation on topic 'packages'
   [Google Slides link to presentation](https://docs.google.com/presentation/d/1hrXaewqivHxVyLq9jCytpMvTzpTxJ-yI_wwBTIthlHI/edit#slide=id.p)
   
  Final presentation
  [Google Slides link to presentation](https://docs.google.com/presentation/d/1bdDMfEQ3tYdK1lGkH5KHnMsGwzbkqkJ0AcXlb6eBV8A/edit#slide=id.g2593bad232c_1_0)

# Steps to replicate:
1.
2.
3.


# Scripts


### Clone the Repository

```bash
git clone https://github.com/RIOT-OS/RIOT.git
```

## Set up NRFDK52840 Board:



## Establish a WireGuard VPN tunnel:



## Setup gnrc_border-router:


Follow the steps below to build and run the GNRC Border Router Example:

1. Navigate to gnrc_border_router file which is located in examples.
      ``` bash
    cd RIOT/examples/gnrc_border_router
     ```
2. Install Nordic's nrfutil. You'll need to install Nordic's nrfutil program to create firmware packages supported by the bootloader and flash them to the device. Make sure nrfutil is installed before proceeding.
      ``` bash
     .nrfutil install nrf5sdk-tools
      ```
3. Set up Serial Port Permissions: Linux systems usually don't give users permission to access the serial port by default. To access the serial port for flashing the device. Either,
 Run nrf-udev to change the permissions:
   ```bash
   sudo dpkg -i nrf-udev_1.0.1-all.deb
   ```
   or,
   ```bash
   sudo adduser <username> dialout
   sudo reboot
   ```

4. Enabling IPV6 forwarding
    ``` bash
    # Check the current forwarding status
      sudo sysctl -a | grep forwa 
    # If the value is '0', enable forwarding by changing it to '1'
      sudo sysctl -w net.ipv6.conf.all.forwarding=1
   ```


6. Find the USB-port to which the dongle has been connected.
     ``` bash
     make list-ttys 
   ```
7. Building GNRC Border example.
    ``` bash
    PORT=/dev/ttyACM3 IPV6_PREFIX=2001:470:7347:c401::/64 BOARD=nrf52840dongle make term flash 
   ```
   
   
   

## Setup emcute_MQTT-SN:



## Setup EC2 instance with IPV6 address

### Prerequisites

Before you begin, make sure you have the following:

- An AWS account
- AWS CLI installed and configured with appropriate permissions

### Step 1: Create VPC with IPv6

1. Go to the AWS Management Console.
2. Navigate to the **VPC Dashboard**.
3. Click on **Create VPC**.
4. Choose **IPv6 CIDR block** and provide the IPv6 block you want to use.
5. Configure other VPC settings as needed.
6. Click on **Create VPC**.

### Step 2: Configure Subnets and Internet Gateway

1. Go to the AWS Management Console.
2. Navigate to the **VPC Dashboard**.
3. Click on **Create Subnet**.
4. Choose **IPv6 CIDR block** and provide the IPv6 block for the subnet.
5. Configure other subnet settings as needed.
6. Click on **Create Subnet**.
7. Create additional subnets following the same steps above.
8. Click on **Internet Gateways** in the left sidebar.
9. Click on **Create Internet Gateway**.
10. Attach the Internet Gateway to your VPC.
11. Go to **Route Tables** and configure the route to the Internet Gateway for IPv6 traffic.

### Step 3: Launch EC2 Instance with IPv6

1. Go to the AWS Management Console.
2. Navigate to the **EC2 Dashboard**.
3. Click on **Launch Instance**.
4. Choose an **Amazon Machine Image (AMI)** for your EC2 instance.
5. Configure the instance details, including the VPC and subnet you created with IPv6 support.
6. Click **Next: Add Storage** and configure storage settings as needed.
7. Click **Next: Add Tags** and add any tags you want to associate with the instance.
8. Click **Next: Configure Security Group** and configure security group rules to allow necessary traffic.
9. Click **Review and Launch**.
10. Review your instance configuration and click **Launch**.
11. Choose an existing key pair or create a new one to access your EC2 instance via SSH.
12. Click **Launch Instances**.
13. Wait until the instance is up and running and the click “Connect” and enter  the EC2 terminal
14. Continue with [Execution of commands on EC2](#execution-of-commands-on-ec2)

### Execution of commands on EC2
On EC2 Instance run the following commands:
``` bash
#Update the list of repositories with one containing the latest version of #Mosquitto and update the package lists
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update

#Install the Mosquitto broker, Mosquitto clients and the aws cli
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
sudo apt install awscli
```

### Accessing the EC2 Instance

 Use the key pair you selected during instance launch to SSH into the EC2 instance with its IPv6 address.

  ``` bash
  ssh -i MQTT_BROKER.pemubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872
  ```

## Mosquitto RSMB (Really Small Message Broker) Broker:

RSMB is a lightweight MQTT and MQTT-SN capable broker developed by Eclipse.

### Building RSMB

To build RSMB, follow these steps:

1. Clone the repository  and navigate to the source folder file (src):
   ``` bash
   git clone https://github.com/eclipse/mosquitto.rsmb.git
   cd mosquitto.rsmb/rsmb/src
   ```


2. Create a configuration file. Save the following to `RSMBconfig.conf\:
   ``` 
   # add some debug output
   trace_output protocol
   # listen for MQTT-SN traffic on UDP port 1885
   listener 1885 INADDR_ANY mqtts
   ipv6 true
   # listen to MQTT connections on tcp port 1886
   listener 1886 INADDR_ANY
   ipv6 true

   ```

### Running RSMB

1. SSH into your EC2 instance:
   ``` bash
   ssh -i MQTT_BROKER.pemubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872  
   ```
2. Copy the RSMB executable and configuration file to your EC2 instance:
   ``` bash
   scp -r/Downloads/RIOT-master/examples/emcute_mqttsn ubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872:
   ```

3. Start the broker:
   ``` bash
   ./broker_mqtts RSMBconfig.conf
   ```
 #### Some useful information
 If some processes are already running on a specific port on the broker, then the below provided commands serve the purpose of checking for processes running on a specific port and then terminating a process running on that port if needed.
 ```bash 
 # Check for processes running on port 1886 and for the PID 
sudo lsof -i :1886

 # If you find a process running on port 1886 and it has a PID of 904, terminate it
sudo kill 904  
```

 ## Publisher script 



## Grafana Installation with NGINX as a Reverse Proxy

This repository provides step-by-step instructions for installing Grafana and configuring NGINX as a reverse proxy to access Grafana.

### Prerequisites

Before you begin, ensure you have the following:

- A Linux-based system (this guide uses Ubuntu).Establish a WireGuard VPN tunnel EC2 IP address.
- Administrative access to the server.
- Domain name or public IP address pointing to the server(this case)

### Installation


 Step 1: Install Grafana
``` bash
sudo apt-get update
sudo apt-get install -y apt-transport-https
sudo apt-get install -y software-properties-common wget
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
sudo apt-get update
sudo apt-get install -y grafana
```

Step 2: Start and enable the Grafana service
``` bash
sudo systemctl start grafana-server
sudo systemctl enable grafana-server
```

Step 3: Install NGINX
``` bash
sudo apt-get install -y nginx
```
Step 4: Configure NGINX as a Reverse Proxy for Grafana
Create a new NGINX server block configuration file ( grafana.conf) using a text editor
``` bash
sudo nano /etc/nginx/sites-available/grafana.conf
```
 Add the following configuration to the file. Replace your_domain.com with your domain name or public IP
Save the file and exit the text editor.
```
server {
    listen 80;
    ec2-54-234-100-189.compute-1.amazonaws.com;  # Replace with your domain name or public IP

    location / {
        proxy_pass http://localhost:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
    
}
```

### Enable the NGINX server block configuration
``` bash
sudo ln -s /etc/nginx/sites-available/grafana.conf /etc/nginx/sites-enabled/
```

### Test the NGINX configuration
``` bash
sudo nginx -t
```

### If there are no errors, restart NGINX
``` bash
sudo systemctl restart nginx
```
### Access Grafana

Open a web browser and navigate to http://your_public_ip of EC2 instance: 3000. You should see the Grafana login page.

1.  Enter the default username and password (admin/admin).
2.  Follow the prompts to change the password.

If everything is set up correctly, you should be able to access and use Grafana through the NGINX reverse proxy.



## How everything works
In Order to send data from NRFDK52840 board  to the AWS cloud the 
application consists of 9 different services. 
1. Sensor Data Collection Using nRFDK52840 Board and DHT11 Sensors
2. MQTT-SN execution
3. Border-Router
4. VPN WireGuard
5. Mosquitto MQTT Broker on AWS
6. Publisher script on EC2 instance 
7.  SQLite Database
8. Grafana with Nginx
9. Using an IPv4 address to access a web browser

### Sensor Data Collection Using nRFDK52840 Board and DHT11 Sensors:

The nRF52840 DK board is running RIOT OS, and the SAUL registry is used to access and read data from the DHT11 sensors. The SAUL interface is used to collect temperature  data from the DHT11 sensors.

### MQTT-SN execution:

The nRFDK52840 board publishes the collected sensor data as MQTT-SN messages using the emcute MQTT-SN library. MQTT-SN is a sensor network protocol that is efficient and ideal for low-power sensors.

### Border-Router

Border Router with IPv6 Address: The Border Router serves as a link between the local IPv6-based sensor network and the external IPv6 network (the internet or cloud services). It enables communication between the nRF DK board, which functions on an IPv6 network, and the external network with IPv6 capability.

### VPN WireGuard:

Using WireGuard, the nRF DK board makes a safe and encrypted VPN connection with an AWS EC2 instance. WireGuard protects and secures data exchanged between the nRF DK board and the EC2 instance.

### Instance of RSMB Broker in EC2:

The RSMB (Really Small Message Broker) broker is hosted on the AWS EC2 instance, which serves as the primary message hub. Through the VPN connection, RSMB receives MQTT-SN messages from the nRF DK board.
The broker processes and prepares the incoming data for storage.

### MQTT Publisher Script:

The MQTT publisher script, which runs on the EC2 instance, works as a MQTT client, subscribing to particular MQTT topics on the RSMB broker.
When the RSMB broker receives MQTT-SN messages from the nRF DK board and converts them to MQTT messages, they are published to the appropriate MQTT topics. The MQTT publisher script monitors these MQTT topics and gets sensor data from the RSMB broker.
When the sensor data is received, the script stores it in a SQLite database for further analysis and retrieval.

### SQLite Database: 

### Grafana with Nginx: 

Grafana is installed on the EC2 instance in order to visualize sensor data saved in the SQLite database. Nginx serves as a reverse proxy, securely redirecting incoming requests to the Grafana web interface.

### Using an IPv4 address to access a web browser:

Users can access Grafana's web interface using their web browsers and the EC2 instance's public IPv4 address. The Grafana interface visualizes sensor data in real time, allowing for data analysis and decision-making.










