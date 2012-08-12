/*
 * Firmata is a generic protocol for communicating with microcontrollers
 * from software on a host computer. It is intended to work with
 * any host computer software package.
 *
 * To download a host software package, please clink on the following link
 * to open the download page in your default browser.
 *
 * http://firmata.org/wiki/Download
 */

/* Supports as many digital inputs and outputs as possible.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>

//
//
const int threshold = 150;
const int piezo0 = A0; int sensor0 = 0;
const int piezo1 = A1; int sensor1 = 1;
const int piezo2 = A2; int sensor2 = 2;
const int piezo3 = A3; int sensor3 = 3;
const int piezo4 = A4; int sensor4 = 4;
const int piezo5 = A5; int sensor5 = 5;

int estado0 = LOW;
int estado1 = LOW;
int estado2 = LOW;
int estado3 = LOW;
int estado4 = LOW;
int estado5 = LOW;

int digital0 = 4;
int digital1 = 5;
int digital2 = 6;
int digital3 = 7;
int digital4 = 8;
int digital5 = 9;
//
//




byte previousPIN[TOTAL_PORTS];  // PIN means PORT for input
byte previousPORT[TOTAL_PORTS]; 

void outputPort(byte portNumber, byte portValue)
{
    // only send the data when it changes, otherwise you get too many messages!
    if (previousPIN[portNumber] != portValue) {
        Firmata.sendDigitalPort(portNumber, portValue); 
        previousPIN[portNumber] = portValue;
    }
}

void setPinModeCallback(byte pin, int mode) {
    if (IS_PIN_DIGITAL(pin)) {
        pinMode(PIN_TO_DIGITAL(pin), mode);
    }
}

void digitalWriteCallback(byte port, int value)
{
    byte i;
    byte currentPinValue, previousPinValue;

    if (port < TOTAL_PORTS && value != previousPORT[port]) {
        for(i=0; i<8; i++) {
            currentPinValue = (byte) value & (1 << i);
            previousPinValue = previousPORT[port] & (1 << i);
            if(currentPinValue != previousPinValue) {
                digitalWrite(i + (port*8), currentPinValue);
            }
        }
        previousPORT[port] = value;
    }
}

void setup()
{
    Firmata.setFirmwareVersion(0, 1);
    Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
    Firmata.attach(SET_PIN_MODE, setPinModeCallback);
    Firmata.begin(57600);
    
    pinMode(digital0, OUTPUT);
    pinMode(digital1, OUTPUT);
    pinMode(digital2, OUTPUT);
    pinMode(digital3, OUTPUT);
    pinMode(digital4, OUTPUT);
    pinMode(digital5, OUTPUT);
}

void loop()
{
    byte i;

    for (i=0; i<TOTAL_PORTS; i++) {
        outputPort(i, readPort(i, 0xff));
    }

    while(Firmata.available()) {
        Firmata.processInput();
    }
    
    //
    
    //
    
    
    sensor0 = analogRead(piezo0);
  sensor1 = analogRead(piezo1);
  sensor2 = analogRead(piezo2);
  sensor3 = analogRead(piezo3);
  sensor4 = analogRead(piezo4);
  sensor5 = analogRead(piezo5);
  
  if (sensor0>=threshold) {
    estado0 = !estado0;
    digitalWrite(digital0, estado0);
    

  }

  if (sensor1>=threshold) {
    estado1 = !estado1;
    digitalWrite(digital1, estado1);

  }
  
  if (sensor2>=threshold) {
    estado2 = !estado2;
    digitalWrite(digital2, estado2);

  }
  
  if (sensor3>=threshold) {
    estado3 = !estado3;
    digitalWrite(digital3, estado3);

  }
  
  if (sensor4>=threshold) {
    estado4 = !estado4;
    digitalWrite(digital4, estado4);

  }
  
  if (sensor5>=threshold) {
    estado5 = !estado5;
    digitalWrite(digital5, estado5);

  }
  
  //
  //
  
  
    
}
