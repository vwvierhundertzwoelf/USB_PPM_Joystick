# USB PPM Joystick
An Arduino adapter for RC remote control PPM signals to USB HID Joystick.

Many (semi) professionl remote controls can output their control signal via a connector. Usualy the signal is [PPM](https://en.wikipedia.org/wiki/Pulse-position_modulation) modulated.

If you want to train your steering skills before lifting off your RC helicopter you should consider using a RC simulator first. With this adapter-sketch you can use your original remote control as an joystick.  

This sketch uses a slightly modified version of the vusb library in order to work with the Arduino framework, added some `const` before `PROGMEM` and changed the typedef of `byte` to `uchar`.
The sketch is based on the UsbJoystick demo from Michel Gutlich (example included in library).

This sketch relies heavily on the USB_PPM_Joystick Adapter by wapata.

Changed PPM Read Method according to 
https://miscircuitos.com/how-to-read-rc-radio-signals-with-arduino-using-ppm-signal-tutorials/

This now works with Modern Arduino and PlatformIO

###Requirements
PlatformIO

###Installation

Use PlatformIO in VSCode or ATOM IDE

##Hardware 
This has only been tested with Arduino NANO, should work with other Atmega328 or Atmega168 based boards as well.

The electric scheme included does not show all the Arduino connections and additions. It just shows a kind of bare minimum required. The voltage regulator is only required because USB signals are 3.3 V based while the USB power is 5 V.
###Connections
Arduino D2 -> USB D+ (fixed)  
Arduino D3 -> USB D- (fixed)  
Arduino D4 -> 1.5 kOhm -> USB D- *(optional)*  
Arduino D8 -> PPM input *(changeable in code)*


