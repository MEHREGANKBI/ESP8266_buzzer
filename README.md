# ESP8266 Buzzer

## Tables of contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Notes](#notes)


## Introduction
This project is a simple, lightweight visual-buzzer/blinker desgined to run on ESP8266 nodeMCU modules. This code takes advantage of the Wifi capability of the MCU to create a HTTP webserver that listens for requests (i.e the instructions) received from the user and if needed, serves a response as well. Because of the fact that this code uses popular technologies like Wifi, HTTP, and HTML, it allows the pager to be accessible from almost any electronic device used on a day-to-day basis. In other words, its simplicity is its strength.


## Installation
The guide below is intended for those people who use the arduino IDE. If you use other tools to compile the code and/or dump the binary onto the MCU board, you should consult their manuals.

1- First off, set up the Arduino IDE to load the packaged needed for development with esp8266 boards. This link is a good starting point: https://randomnerdtutorials.com/installing-esp8266-nodemcu-arduino-ide-2-0/

2- Once done with the board setup, clone/download this repository. (You'll need to unzip the folder if you choose to download)

3- Open the buzzer.ino file of the src folder using the IDE, enter the **ssid** and **password** of your router inside the code. You do not need the "index.html" file. It is there for demonstration purposes. After entering your router's credentials, click the upload button. When the binary is fully located onto the board, the binary will also print debugging messages to the serial monitor.

4- You can detach the board from your PC, and connect it to a reliable power source (micro USB or a traditional battery) for normal use. Note that the board should remain in your router's range.


## Notes

*The code is written in a way that if the wifi connection is lost for whatever reason, it'll try to reconnect.*

*If the built-in LED is on and not blinking, it means the MCU board is busy and will not process requests.*

*For more info, consult the license file for this project.*