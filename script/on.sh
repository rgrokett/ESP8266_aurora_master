#!/bin/sh
# Linux command-line program to turn on the Aurora Master and jump to patern 2
#
# 

# CHANGE FOR YOUR IP ADDRESS
ESP_IP="aurora"


# Make sure the GPIO pin is set LOW. Probably not needed, but doesn't hurt
curl http://$ESP_IP/gpio/0

sleep 1
# Turn on the Aurora Master and jump to second pattern
curl http://$ESP_IP/gpio/step
sleep 1
curl http://$ESP_IP/gpio/step
