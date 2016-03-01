/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "HX711.h"

// HX711.DOUT	- pin #3
// HX711.PD_SCK	- pin #4

 HX711 scale(A0,A1);

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            A2

#define tareHigh 6
#define tareLow  5


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(212,97,141,141);  // numeric IP for Google (no DNS)
// char server[] = "";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
//char buf[100];
 int i=0;

int korr=-3673;
double scale_g=5.17857;

//***************** settings **********************
  
int brewingTime=60*5; //brewint time in seconds
int empty=10350; // empty weight but with margin wet filter
int full=11000; // weight with water but with margin
int margin=20;
int updateRate=10;

//************* end settings **********************


int state=0; // 0=empty 1=brewing 2=coffie 3=overful
double level=0; // waterlevel in system 0-100%
int weight=0; // raw value from AD/amp


float calibration_factor = -7050;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("starting!");
  
  // Set pins for tare
   pinMode(tareHigh, INPUT);
   digitalWrite(tareHigh, HIGH);
   pinMode(tareLow, INPUT);
   digitalWrite(tareLow, HIGH);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(2000);
 pixels.begin(); // This initializes the NeoPixel library.
 Serial.println("Setup complete");
 setTimer2(5);		
}

void loop() {
  
  updateTimer();
  updateTimer2();
  weight=updateWeigth();
  // check for tare high or Low
  if (digitalRead(tareHigh)==false) {
    full=weight;
  }
  if (digitalRead(tareLow)==false) {
    empty=weight;
  }
  
  
  debugPrint();
  setState();
  updateLeds(state,coffieLeft(),getTimer(),brewingTime );
 
  if (getTimer2()==0) {
    updateServer();
    setTimer2(updateRate); 
  }
  
}


double updateWeigth() {
 double w= (-scale.get_value()/100+korr)*scale_g;
 //double w=scale.getGram();
 
 return w; 
}

int coffieLeft() {
  double foo=(weight-empty);
  double bar=(full-empty);
  double left=foo/bar*100;
  if (left>100)
    left=100;
  if (left<0)
    left=0;
  return round(left);
}

void debugPrint() {
   Serial.print("Weight: ");
   Serial.print(weight);
   Serial.print(" State: ");
   Serial.print(state);
   Serial.print(" Timer: ");
   Serial.print(getTimer());
   Serial.print(" Time to update: ");
   Serial.print(getTimer2());
   
   Serial.print(" High: ");
   Serial.print(full);
   Serial.print(" Low: ");
   Serial.print(empty);
   
   
   
   Serial.print(" Coffee left: ");
   Serial.println(coffieLeft()); 
}

