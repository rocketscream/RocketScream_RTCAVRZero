#include <RocketScream_RTCAVRZero.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  /* true: external 32.768 kHz crystal */
  /* false: internal 32.768 kHz ULP oscillator */
  RTCAVRZero.begin(false);
  /* Time in seconds, true: repeat, false: once */
  RTCAVRZero.enableAlarm(5, false);
  RTCAVRZero.attachInterrupt(onLed);
}

void loop(void)
{
	
}

void onLed(void)
{
  digitalWrite(LED_BUILTIN, HIGH);
  RTCAVRZero.disableAlarm();
  RTCAVRZero.detachInterrupt();
}
