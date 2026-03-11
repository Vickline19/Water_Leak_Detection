# Water_Leak_Detection_System

A system that monitors the state of leaks and alerts user through telegram notification

## Features

Real time leak detection,

Sensor based monitoring,

Alerts via buzzer and telegram notifications.

## Installation

Clone repository,

Upload code to your ESP8266,

## How to connect componets

Use a 5V Power supply to power the ESP

Connect the anode of the red led to GPIO5 of ESP and cathode to GND

Connect the anode of the green led to GPIO2 of ESP and cathode to GND

Connect the positive signal of the buzzer to GPIO4 and negative side to  Ground

The signal off the water sensor to ADC on the ESP, Positive connects to 5V and negative to GND

## How to receive telegram bot message

Install the telegram APP and create an account

Search for "BotFather" and follow prompts to generate token 

Also search "IDBot" follow  prompts to generate ID

Start the telegram bot you created example in my case "LeakALertBot" in order to able to receive messages

Use the token and id you created in your code as i did in order to connect the system to the bot

## Usage

Run the system and monitor for alerts when leaks occur

## Collaborators

1. Vickline Achieng
2. Masika - Supervisor

