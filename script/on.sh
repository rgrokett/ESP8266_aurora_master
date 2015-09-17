#!/bin/sh
# Linux command-line program to turn on the Aurora Master and jump to patern 2
#
# 

# CHANGE FOR YOUR IP ADDRESS
ESP_IP="192.168.1.83"


# Make sure the GPIO pin is set LOW. Probably not needed, but doesn't hurt
curl http://$ESP_IP/gpio/0

# Turn on the Aurora Master and jump to second pattern
curl http://$ESP_IP/gpio/step
curl http://$ESP_IP/gpio/step
