#include <Ticker.h>
#include <Arduino.h>

//this is for the led blinking 
Ticker ticker;

void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

void StartBlinking(float period)
{
    ticker.attach(period, tick);
}

void StopBlinkingLed()
{
    ticker.detach();
    
    //keep LED OFF (it will blink just on data send...)
    digitalWrite(BUILTIN_LED, HIGH); 
}