#include <RocketScream_RTCAVRZero.h>

volatile bool alarm = false;
uint8_t blink;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  blink = 0;
  
  /* true: external 32.768 kHz crystal */
  /* false: internal 32.768 kHz ULP oscillator */
  RTCAVRZero.begin(false);
  /* Time in seconds, true: repeat, false: once */
  RTCAVRZero.enableAlarm(1, true);
  RTCAVRZero.attachInterrupt(toggle);
}

void loop(void)
{
  if (alarm)
  {
    alarm = false;
    digitalWrite(LED_BUILTIN, CHANGE);
	  
    /* Has LED blink 5 times? */
	  if (++blink == 10)
	  {
	    blink = 0;	
	    RTCAVRZero.disableAlarm();
	    RTCAVRZero.detachInterrupt();
	  }  
  }
}

void toggle(void)
{
  alarm = true;
}
