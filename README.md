
# IoT-cloud-riot
Author: Linta Joseph (1474363), Syed Ahmed Zaki(1322363)

# Architecture
![image]()

# Demonstration 
[Google Drive link to the video](architecture.jpeg)

# Presentation 
   Presentation on topic 'package'
   [Google Slides link to presentation](https://docs.google.com/presentation/d/1hrXaewqivHxVyLq9jCytpMvTzpTxJ-yI_wwBTIthlHI/edit#slide=id.p)
   
  Final presentation
  [Google Slides link to presentation](https://docs.google.com/presentation/d/1bdDMfEQ3tYdK1lGkH5KHnMsGwzbkqkJ0AcXlb6eBV8A/edit#slide=id.g2593bad232c_1_0)

# Steps to replicate:
1.

# Scripts


### Clone the Repository

```bash
git clone https://github.com/RIOT-OS/RIOT.git
```

## Set up NRFDK52840 Board:

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

## Prerequisites

Before you begin, make sure you have the following:

- An AWS account
- AWS CLI installed and configured with appropriate permissions

## Step 1: Create VPC with IPv6

1. Go to the AWS Management Console.
2. Navigate to the **VPC Dashboard**.
3. Click on **Create VPC**.
4. Choose **IPv6 CIDR block** and provide the IPv6 block you want to use.
5. Configure other VPC settings as needed.
6. Click on **Create VPC**.

## Step 2: Configure Subnets and Internet Gateway

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

## Step 3: Launch EC2 Instance with IPv6

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

## Execution of commands on EC2
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

## Accessing the EC2 Instance

 Use the key pair you selected during instance launch to SSH into the EC2 instance with its IPv6 address.

  ``` bash
  ssh -i MQTT_BROKER.pemubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872
  ```




## Mosquitto RSMB (Really Small Message Broker) Broker:

RSMB is a lightweight MQTT and MQTT-SN capable broker developed by Eclipse.

## Building RSMB

To build RSMB, follow these steps:

1. Clone the repository  and navigate to the source folder file (src):
   ``` bash
   git clone https://github.com/eclipse/mosquitto.rsmb.git
   cd mosquitto.rsmb/rsmb/src
   ```

2. Compile the code:
   ``` bash
   make
3. Create a configuration file. Save the following to `RSMBconfig.conf\:
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

## Running RSMB

1. SSH into your EC2 instance:
   ``` bash
   ssh -i MQTT_BROKER.pemubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872  
   ```
2. Copy the RSMB executable and configuration file to your EC2 instance:
   ``` bash
   scp -r -i MQTT_BROKER.pem RIOT-master ubuntu@2600:1f18:6929:5505:5ea4:f15c:41fb:1872:
   ```

3. Start the broker:
   ``` bash
   ./broker_mqtts RSMBconfig.conf
   ```
 ## Publisher script 
 

## Grafana Installation with NGINX as a Reverse Proxy

This repository provides step-by-step instructions for installing Grafana and configuring NGINX as a reverse proxy to access Grafana.

## Prerequisites

Before you begin, ensure you have the following:

- A Linux-based system (this guide uses Ubuntu).
- Administrative access to the server.
- Domain name or public IP address pointing to the server.

## Installation


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

## Enable the NGINX server block configuration
``` bash
sudo ln -s /etc/nginx/sites-available/grafana.conf /etc/nginx/sites-enabled/
```

## Test the NGINX configuration
``` bash
sudo nginx -t
```

## If there are no errors, restart NGINX
``` bash
sudo systemctl restart nginx
```
## Access Grafana

Open a web browser and navigate to http://your_public_ip of EC2 instance: 3000. You should see the Grafana login page.

1.  Enter the default username and password (admin/admin).
2.  Follow the prompts to change the password.

If everything is set up correctly, you should be able to access and use Grafana through the NGINX reverse proxy.



# How everything works
In Order to send data from NRFDK52840 board  to the AWS cloud the 
application consists of 7 different services. 
1. Border-router
2. NRFDK52840 board with driver to supply data
3. Bridge to route MQTT messages from Sensor node  to AWS
4. Mosquitto MQTT Broker on AWS
5. Publisher script on EC2 instance
6. EC2 Instance to receive data on AWS
7. Grafana with nginx

### Border-Router

### NRFDK52840 board with driver to supply data

### Bridge to route MQTT messages from Sensor node  to AWS


### Rsmb Broker in EC2 Instance

### Publisher script on EC2 instance

### EC2 Instance to receive data on AWS


### Grafana with nginx


