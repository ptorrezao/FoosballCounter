#include <Arduino.h>

const int ledPin =  LED_BUILTIN;

void blink(){
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
}

void utils_init(){
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  for (size_t i = 0; i < 3; i++) { 
    digitalWrite(ledPin, LOW);
    delay(250); 
    digitalWrite(ledPin, HIGH);
  }
}