#include <avr/io.h>
#include <avr/interrupt.h>
#include "RocketScream_RTCAVRZero.h"

voidFuncPtr RTC_callBack = NULL;
bool _repeat = false;

/*! \brief RTC initialization.
 *
 */
void RocketScream_RTCAVRZeroClass::begin(bool osc)
{
  uint8_t temp;
  
  // External 32.768 kHz crystal
  if (osc)
  {
    /* Initialize 32.768kHz Oscillator: */
    /* Disable oscillator: */
    temp = CLKCTRL.XOSC32KCTRLA;
    temp &= ~CLKCTRL_ENABLE_bm;
    /* Enable writing to protected register */
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.XOSC32KCTRLA = temp;

    while (CLKCTRL.MCLKSTATUS & CLKCTRL_XOSC32KS_bm)
    {
      ; /* Wait until XOSC32KS becomes 0 */
    }

    temp = CLKCTRL.XOSC32KCTRLA;

    /* SEL = 0 (Use External Crystal): */
    temp &= ~CLKCTRL_SEL_bm;
    /* Enable writing to protected register */
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.XOSC32KCTRLA = temp;

    /* Enable oscillator: */
    temp = CLKCTRL.XOSC32KCTRLA;
    temp |= CLKCTRL_ENABLE_bm;
    /* Enable writing to protected register */
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.XOSC32KCTRLA = temp;
    /* 32.768kHz External Crystal Oscillator (XOSC32K) */
    RTC.CLKSEL = RTC_CLKSEL_TOSC32K_gc;
  }
  // Internal low power crystal
  else
  {
    /* 32.768kHz Internal Crystal Oscillator (INT32K) */
	  RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;
  }
  
  /* Initialize RTC: */
  while (RTC.STATUS > 0)
  {
    ; /* Wait for all register to be synchronized */
  }

  /* Run in debug: enabled */
  RTC.DBGCTRL |= RTC_DBGRUN_bm;
  RTC.CTRLA = RTC_PRESCALER_DIV32768_gc /* 32768 */
              | RTC_RTCEN_bm /* Enable: enabled */
              | RTC_RUNSTDBY_bm; /* Run In Standby: enabled */
               
}

/*! \brief Designate a user defined callback function to the RTC interrupt
 *         service routine.
 *
 */
void RocketScream_RTCAVRZeroClass::attachInterrupt(voidFuncPtr callback)
{
  RTC_callBack = callback;
}

/*! \brief Remove assigned user defined callback function from the RTC interrupt
 *         service routine.
 *
 */
void RocketScream_RTCAVRZeroClass::detachInterrupt(void)
{
  RTC_callBack = NULL;
}

/*! \brief Enable alarm as overflow (periodic) or one shot (compare match).
 *
 */
void RocketScream_RTCAVRZeroClass::enableAlarm(uint16_t period, bool repeat)
{
  _repeat = repeat;

  while (RTC.STATUS > 0)
  {
    ; /* Wait for CNT register to be synchronized */
  }

  /* Reset counter */
  RTC.CNT = 0;
  
  if (_repeat)
  {
    /* Set period */
    RTC.PER = period - 1;
    /* Enable Overflow Interrupt */
    RTC.INTCTRL |= RTC_OVF_bm;
  }
  else
  {
    /* Set period */ 
	  RTC.CMP = period - 1;
    
	  /* Enable Compare Match Interrupt */
	  RTC.INTCTRL |= RTC_CMP_bm;
  }
}

/*! \brief Disable alarm.
 *
 */
void RocketScream_RTCAVRZeroClass::disableAlarm(void)
{
  if (_repeat) RTC.INTCTRL &= ~RTC_OVF_bm;
  else RTC.INTCTRL &= ~RTC_CMP_bm;
}

/*! \brief RTC Interrupt Service Routine (ISR).
 *         User defined callback function will be executed if assigned.  
 *
 */
ISR(RTC_CNT_vect)
{
  /* Clear flag by writing '1': */
  if (_repeat) 
  {
    RTC.INTFLAGS = RTC_OVF_bm;
  }
  else 
  {
    RTC.INTFLAGS = RTC_CMP_bm;
  }
  
  if (RTC_callBack != NULL)
  {
	  RTC_callBack();
  }
}

RocketScream_RTCAVRZeroClass RTCAVRZero;

