/*
Zigbee test
 ~ Simple Arduino - xBee Receiver sketch ~

  Read an PWM value from Arduino Transmitter to fade an LED
  The receiving message starts with '<' and closes with '>' symbol.
  
  Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */
// Imports
#include <Wire.h>
#include<string>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <XBee.h>

// Defines
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Zigbee
#define SERIES_2 true;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Constants
const int ledPin = A0;

//Variables
bool started = false; //True: Message is strated
bool ended = false;   //True: Message is finished 
char incomingByte;    //Variable to store the incoming byte
char msg[3];          //Message - array from 0 to 2 (3 values - PWM - e.g. 240)
byte index;           //Index of array

//Zigbee variables
XBee xbee = XBee();
XBeeResponse response;

void DisplayMessage(String msg){
  display.clearDisplay();
  display.setCursor(0,25);
  display.println(msg);
  display.display();
}

void SerialAndDisplayMessage(String msg, int wait){
  DisplayMessage(msg);
  Serial.println(print);
  delay(wait);
}

void setup() {
  //Start the serial communication
  Serial.begin(9600); //Baud rate must be the same as is on xBee module
  pinMode(ledPin, OUTPUT);

  //display warnings
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    
  }
    //display out startup message
    display.setTextSize(1);
    display.setTextColor(WHITE);
    SerialAndDisplayMessage("Zigtest reciver test", 500);
}

void loop() {
  while (Serial.available()>0){
    //Read the incoming byte
    incomingByte = Serial.read();
    //Start the message when the '<' symbol is received
    if(incomingByte == '<')
    {
      started = true;
      index = 0;
      msg[index] = '\0'; // Throw away any incomplete packet
    }
     //End the message when the '>' symbol is received
    else if(incomingByte == '>') {
      ended = true;
      break; // Done reading - exit from while loop!
    }
     //Read the message!
    else {
      if(index < 4) { // Make sure there is room 
        msg[index] = incomingByte; // Add char to array
        index++;
        msg[index] = '\0'; // Add NULL to end
      }
    }
  }
 
  if(started && ended) {
    int value = atoi(msg);
    analogWrite(ledPin, value);
    Serial.println(value); //Only for debugging

    //display out
    delay(1000);
    display.clearDisplay();
    display.setCursor(0,25);
    display.println(value);
    display.display();

    //reset
    index = 0;
    msg[index] = '\0';
    started = false;
    ended = false;
  }
}
