#ifndef RocketScream_RTCAVRZero_h
#define RocketScream_RTCAVRZero_h

#include "Arduino.h"

typedef void(*voidFuncPtr)(void);

class RocketScream_RTCAVRZeroClass
{
	public:
    void begin(bool osc);
    void enableAlarm(uint16_t period, bool repeat);
    void disableAlarm();
    void attachInterrupt(voidFuncPtr callback);
    void detachInterrupt();
		
	private:
};

extern RocketScream_RTCAVRZeroClass RTCAVRZero;

#endif
