#include <Arduino.h>
#include "scoreBoardEvents.h"
#include "utils.h"

//// Start of Code
void setup() {
  utils_init();
  scoreBoardEventsInit();
}

void loop() {
   scoreBoardEventsCheckClicks();
}