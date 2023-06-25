/**
 * XBee example for series 2


#include <XBee.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// XBee object for sending and reading packets.
XBee xbee = XBee();


//const int RouterMacAdress = 0013A2004155B9BA
// SH + SL for 64 bit adress
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x4155B9BA);
ZBTxRequest zbTx;
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

uint8_t payload[] = {0, 0};

int statusLed = 13;

void BlinkLED(int LED, int ms, int blinkTimes) {
  for(int i; i > blinkTimes; i++) {
    digitalWrite(LED, !digitalRead(LED));
    delay(ms);
  }
}


void setup() {
  pinMode(statusLed, OUTPUT);

  Serial.begin(9600);
  xbee.setSerial(Serial);

  //Display setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,25);
}

void loop() {
  // Send 0x10: ZigBee Transmit Request (ZNet, ZigBee)
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

  display.clearDisplay();
  display.println("Send Packet");
  display.display();

  //BlinkLED(statusLed, 100, 1);

  xbee.send(zbTx);

  // Reading response
  if (xbee.readPacket(500)) {            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // Check status, on the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        BlinkLED(statusLed, 50, 5);
        display.clearDisplay();
        display.println(txStatus.getDeliveryStatus());
        display.display();
      } else {
        // No response was recievied
        BlinkLED(12, 500, 1);
        display.clearDisplay();
        display.println("No response");
        display.println(txStatus.getDeliveryStatus());
        display.display();
      }
    }
  } else if (xbee.getResponse().isError()) {
      BlinkLED(12, 500, 2);
      display.clearDisplay();
      display.println("Error code: ");
      display.println(xbee.getResponse().getErrorCode());
      display.display();
  } else {
    // Response timeout, happens when is not connected
    BlinkLED(12, 500, 3);
    display.clearDisplay();
    display.println("Not connected");
    display.display();
  }

  BlinkLED(11, 100, 1);
  display.clearDisplay();
  display.println("Done");
  display.display();
  delay(1000);
}*/

/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 
  XBee guides and examples
  https://github.com/andrewrapp/xbee-arduino/blob/master/XBee.h
  https://github.com/andrewrapp/xbee-arduino/blob/wiki/DevelopersGuide.md         
  
 */

#include <XBee.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
This example is for Series 2 XBee
 Sends a ZB TX request with the value of analogRead(pin5) and checks the status response for success
*/

// create the XBee object
XBee xbee = XBee();

// SH + SL Address of receiving XBee 0013A2004155B9BA
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x4155B9BA);
ZBTxRequest zbTx;
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int value = 0;
uint8_t payload[] = {0, 0};

int statusLed = LED_BUILTIN;
int errorLed = 12;

int sensorPin = A0;

void BlinkLED(int LED, int delayMs, int blinkTimes) {
  for(int i = 0; i < blinkTimes * 2; i++) {
    digitalWrite(LED, !digitalRead(LED));
    delay(delayMs);
  }
}

// break down 10-bit reading into two bytes and place in payload. https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
void PayloadFromAnalogRead(int analogPin) {
  value = analogRead(analogPin);
  payload[0] = value >> 8 & 0xff;
  payload[1] = value & 0xff;
}

void WriteDisplay(char * text) {
  display.clearDisplay();
  display.setCursor(0,25);
  display.println(text);
  display.display();
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);

  Serial.begin(9600);
  xbee.setSerial(Serial);

  //Display setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,25);
  WriteDisplay("Starting...");
}

void loop() {   
  PayloadFromAnalogRead(sensorPin);

  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

  WriteDisplay("Sending...");
  xbee.send(zbTx);

  // flash TX indicator
  BlinkLED(statusLed, 500, 1);

  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        BlinkLED(statusLed, 50, 5);
        WriteDisplay("SUCCESS");
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        BlinkLED(errorLed, 500, 3);
        WriteDisplay("No device found");
      }
    }
  } else if (xbee.getResponse().isError()) {
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());
    BlinkLED(errorLed, 100, 1);
    WriteDisplay("ERROR");
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
    BlinkLED(errorLed, 100, 2);
    WriteDisplay("Timeout");
  }

  delay(500);
}

