#include <Arduino.h>
#include "scoreBoardEvents.h"

int SIGNAL_PIN = D5;               
int LED_PIN = D4;               
int state = 0;            //  Current state of the sensor
int lastState = 0;   
//// Start of Code
void setup() {
  utils_init();
  scoreBoardEventsInit();
  
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  scoreBoardEventsCheckClicks();
  state = digitalRead(SIGNAL_PIN);
  if(state!=lastState) {
  
    if(state==HIGH) {
      teamAScore += 1;
      showResult();
      blink();
    }
    else
    {
      showResult("*");
    }
    

  lastState=state;
    delay(500);
  } 

}