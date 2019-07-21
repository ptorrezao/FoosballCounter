#include <Arduino.h>
#include "scoreBoardEvents.h"

//// Start of Code
void setup() {
  utils_init();
  scoreBoardEventsInit();
}

void loop() {
  scoreBoardEventsCheckClicks();
}