#!/bin/sh
# Linux command-line program to turn on the Aurora Master and jump to patern 2
#
#

# CHANGE FOR YOUR IP ADDRESS
ESP_IP="192.168.1.83"


# Make sure the GPIO pin is set LOW. Probably not needed, but doesn't hurt
curl http://$ESP_IP/gpio/0

# Now rotat thru the other paterns until reaching OFF
# Note this assumes sitting on pattern 2 (on.sh) 
# Adjust number of steps to your needs
# Since there is no feedback, you need to watch your Aurora
# This could have been a loop, but its just too simple to need that!
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
