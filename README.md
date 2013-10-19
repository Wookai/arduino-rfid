#arduino-rfid

A short example of how to read 125 kHz RFID tags using an Arduino and a RMD6300 RFID module

## Required hardware

* [Arduino Uno](http://arduino.cc/en/Main/ArduinoBoardUno) (or other Arduino)
* [125Khz RFID module RDM6300 - UART](http://imall.iteadstudio.com/im120618002.html)
* Breadboard, cables, LEDs

## How to use

* Simply plug the antenna, as well as the power, ground and TX pins of the RFID module to the Arduino (you can find the pins description in the [datasheet](http://cdn.boxtec.ch/pub/iteadstudio/DS_IM120618002_RDM6300.pdf)). The TX pin of the module should connect to the RX pin of the Arduino.
* To use the LEDs as success/error indicators, plug two LEDs to the Arduino (in our code, we use pin 10 and 13)
* Using the Arduino IDE, compile and upload the code to the Arduino. Note that you have to *unplug* the cable connecting to the RX pin of the Arduino to be able to upload the code.
* Put one of your RFID tags close to the antenna and watch! You can use the serial monitor of the Arduino IDE (Ctrl+Shift+M) to see the messages we are printing, and note down the IDs of your tags if you don't know them.