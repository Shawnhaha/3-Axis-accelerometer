#include "Energia.h"
#include "SPI.h"
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

long previousMillis = 0;        // will store last time LED was updated
long interval = 1000;           // interval at which to blink (milliseconds)

const int ledGreen =  38;      // the number of the LED pin
const int interruptPin1 = 33;    //S1
const int interruptPin2 = 32;    //S2
const int interruptPin3 = PUSH1;            //reset button
int inS = 0;
int deS = 0;
int reS = 0;
int greenState = LOW;             // ledState used to set the LED

const int xpin = 23;                  // x-axis of the accelerometer
const int ypin = 24;                  // y-axis
const int zpin = 25;                  // z-axis (only on 3-axis models)

void setup() {
  analogReadResolution(12);
 
  // initialize the LED pins as  output:
  pinMode(ledGreen, OUTPUT);     

  // initialize the pushbutton pin as an input:
  pinMode(interruptPin1, INPUT_PULLUP);     
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP); 
  attachInterrupt(interruptPin1, increase, RISING);
  attachInterrupt(interruptPin2, decrease, RISING);
  attachInterrupt(interruptPin3, rst, RISING);
  myScreen.begin();
  myScreen.setFontSize(0);
}

void loop() {
    int x = 0;
    int y = 0;
    
    myScreen.gText((myScreen.screenSizeX()-20*myScreen.fontSizeX())/2, 10, "3-Axis Accelerometer");
    
    myScreen.gText(0, 30, "Input tilt(x) angle:"); 
    while(reS == 0) {
        if (inS == 1) {
          if (x < 90)
            x++;
          inS = 0; 
        }
        if (deS == 1) {
          if (x > -90)
            x--;
          deS = 0; 
        }
      myScreen.gText(0, 40, String(x) + "     "); 
    }
    reS = 0;
      
    myScreen.gText(0, 50, "Input rotate(y) angle:");
    while(reS == 0) {
      if (inS == 1) {
        if (y < 90)
          y++;
        inS = 0; 
      }
      if (deS == 1) {
        if (y > -90)
          y--;
        deS = 0; 
      }
      myScreen.gText(0, 60, String(y) + "     "); 
    }
    reS = 0;
    
    myScreen.gText(0, 70, "Current angle (x, y):");
    while (1) {
      unsigned long currentMillis = millis();
          if(currentMillis - previousMillis > 500) {
            // save the last time sampled 
            previousMillis = currentMillis;   

            int Ax = ((int) analogRead(xpin)) - 2048;
            int Ay = ((int) analogRead(ypin)) - 2048;
            int Az = ((int) analogRead(zpin)) - 2048;
            int x0 = atan(Ax/sqrt(Ay*Ay + Az*Az))*57.296;
            int y0 = atan(Ay/sqrt(Ax*Ax + Az*Az))*57.296;
            myScreen.gText(0, 80, String(x0) + ", " + String(y0) + "          ");

            double xe = abs(x0*0.025);
            double ye = abs(y0*0.025);
            if (abs(x-x0) <= xe && abs(y-y0) <= ye){
              tone(40, random(100,5000), 200);
              myScreen.gText(0, 90, "Matched!");
              myScreen.gText(0, 100, "Reset?");
              while (reS == 0){
              currentMillis = millis();
              if(currentMillis - previousMillis > interval) {
                // save the last time you blinked the LED 
                previousMillis = currentMillis;   

                // if the LED is off turn it on and vice-versa:
                if (greenState == LOW)
                greenState = HIGH;
                else
                greenState = LOW;
                // set the LED with the ledState of the variable:
                digitalWrite(ledGreen, greenState);
              }
            }
            digitalWrite(ledGreen, LOW);
            myScreen.clear();
            reS = 0;
            break;
          }
       }
       reS = 0;
    }
}

void increase() {
  inS = 1;
}

void decrease() {
  deS = 1;
}

void rst() {
  reS = 1;
}
