#ifndef INCLUDE_DEBOUNCE
#define INCLUDE_DEBOUNCE

/*
 * Switch Debouncing Class
 * Mike Hilton, Eckerd College
 * 
 * This class implements a software-debounced switch.
 */

class Debounce {
  private:
    const int DEFAULT_DELAY = 4;      // the default debounce delay, in milliseconds    
    unsigned long debounceDelay;      // the actual debounce delay, in milliseconds
    unsigned long ignoreTimeout;      // the expiration time for the current ignore window 
    unsigned long ignoreWindow;       // the length of the ignore window, in milliseconds
    unsigned long lastActivationTime; // the time last steady state period began, in milliseconds
    unsigned long lastDebounceTime;   // the last time the steady state was toggled
    int lastFlickerableState;         // the previous flickerable state   
    int steadyState;                  // the current steady state

    void commonInit();                
    
  public:
    Debounce();
    Debounce(unsigned long debounce_delay, unsigned long ignore_window);

    unsigned long activationTime();               // the time last steady state period began, in milliseconds
    int isIgnoring(unsigned long currentMillis);  // returns 1 if ignore window has not expired
    bool serviced;                                // flags if the client has responded to the switch being pressed    
    int state();                                  // returns steady state
    int update(int currentValue, unsigned long currentMillis);     // update the debounce state with the current switch value
    

};


#endif
