#include <Arduino.h>

/*
Anschluss: 
  D+ auf D2
  D- auf D3
  1.5k D- PullUp auf D4
  PPM-In auf D8
*/

#include "UsbJoystick.h"

#define CHANNELS 6 
#define READ_PIN 8

unsigned short a2dValue;
unsigned char high;
unsigned char low;
unsigned char temp;
unsigned char report[8];

unsigned int channel[CHANNELS]; 
unsigned int lastReadChannel[CHANNELS]; 
unsigned int counter=0; 

unsigned int pulseUpTime, pulseLowTime;
boolean lastPinState = LOW;
int numCurPulse=-1;

void setup() {
  pinMode (READ_PIN, INPUT_PULLUP);
  usbDeviceConnect();
  lastPinState = digitalRead(READ_PIN);
}
void calculateReport();
void loop () {
  UsbJoystick.refresh(); // Let the AVRUSB driver do some houskeeping
  calculateReport(); // Jump to our port read routine that orders the values
  UsbJoystick.sendJoystick(report[0],report[1],report[2],report[3],report[4],report[5],report[6],report[7]); // send the values
}

void calculateReport() {  //The values read from the analog ports have to be ordered in a way the HID protocol wants it; a bit confusing.

  if (pulseIn(8, HIGH, 50000) > 3000) //If pulse > 3000 useconds, continues
  {
    for (int i = 0; i <= CHANNELS - 1; i++) //Read the pulses of the channels
    {
      channel[i] = pulseIn(8, HIGH,3000);
    }
    for (int i = 0; i <= CHANNELS - 1; i++) //Average the pulses
    {
      if ((channel[i] > 2000) || (channel[i] < 100)) //If channel > max range, chage the value to the last pulse
      {
        channel[i] = lastReadChannel[i];
      }

      else
      {
        channel[i] = (lastReadChannel[i] + channel[i]) / 2; //Average the last pulse eith the current pulse
                                             //increment counter
      }
    }
  }
  
  a2dValue = channel[0];
  high = a2dValue >> 8;
  low = a2dValue & 255;
  report[0] = low;
  temp = high;

  a2dValue = channel[1];
  high = a2dValue >> 6;
  low = a2dValue & 63;
  report[1] = (low << 2) + temp;
  temp = high;

  a2dValue =channel[3];
  high = a2dValue >> 4;
  low = a2dValue & 15;
  report[2] = (low << 4) + temp;
  temp = high;

  a2dValue = channel[2];
  high = a2dValue >> 2;
  low = a2dValue & 3;
  report[3] = (low << 6) + temp;
  temp = high;

  high = 0;
  low = 0;
  report[4] = temp;
  temp = high;

  a2dValue = channel[4];
  high = a2dValue >> 8;
  low = a2dValue & 255;
  report[5] = low + temp;
  temp = high;

  a2dValue = channel[5];
  high = a2dValue >> 6;
  low = a2dValue & 63;
  report[6] = (low << 2) + temp;
  temp = high;

  // 4 buttons , tossed around

  report[7] = (temp & 15);

}
