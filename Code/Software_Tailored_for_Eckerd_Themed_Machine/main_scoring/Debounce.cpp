/*
   Switch Debouncing Class
   Mike Hilton, Eckerd College

   This class implements a software-debounced switch.
*/

#include "Debounce.h"

Debounce::Debounce() {
  // Create a Debounce instance with the default delay

  debounceDelay = DEFAULT_DELAY;
  ignoreWindow = 0;
  commonInit();
}


Debounce::Debounce(unsigned long debounce_delay, unsigned long ignore_window) {
  // Create a Debounce instance with a specific debounce delay and ignore window
  // INPUTS
  //  debounce_delay    length of time (in milliseconds) the switch must be in a 
  //                      steady state before current state will be changed
  //  ignore_window     length of time (in milliseconds) that any changes in switch state
  //                      are ignored after a valid change in switch state

  debounceDelay = debounce_delay;
  ignoreWindow = ignore_window;
  commonInit();
}


void Debounce::commonInit() {
  // Initialize actions that are common between all overloaded intialization methods

  ignoreTimeout = 0;
  lastActivationTime = 0;
  lastDebounceTime = 0;
  lastFlickerableState = 0;
  serviced = false;
  steadyState = 0;  
}


unsigned long Debounce::activationTime(){
  // Returns the time last steady state period began, in milliseconds
  return lastActivationTime;
}

    
int Debounce::isIgnoring(unsigned long currentMillis) {
  // Returns 1 if the ignore window has not expired.
  return ((steadyState == 1) && (currentMillis < ignoreTimeout));  
}


int Debounce::state() {
  // Returns the current steady state of the switch
  return steadyState;
}


int Debounce::update(int currentValue, unsigned long currentMillis) {
  // Updates the state of the switch based on the current value of the hardware.
  // INPUTS
  //  currentValue    current value of the switch hardware
  //  currentMillis   time when the switch value was read
  // RETURNS
  //  The current steady state of the switch

  if (currentValue != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = currentMillis;
    lastFlickerableState = currentValue;
  }

  if ((currentMillis - lastDebounceTime) >= debounceDelay) {
    // whatever the currentValue is at, it's been there for longer than the debounce delay
  
    if (steadyState != currentValue) {
      if ((currentValue == 1) && (currentMillis >= ignoreTimeout)) {
        // the last time the switch came on was longer ago than the ignore window, so the
        // steady state can turn on again
        steadyState = 1;
        lastActivationTime = lastDebounceTime;
        serviced = false;
      } else if (currentValue == 0) {
        // there is no ignore window for turning the switch off
        steadyState = 0;
        lastActivationTime = lastDebounceTime;
        ignoreTimeout = lastActivationTime + ignoreWindow;
        serviced = false;
      }
    }
  }

  return steadyState;
}
