# RTCAVRZero
A minimalistic RTC (Real Time Counter) library for the megaAVR 0-series MCU. 
Not to be confused with RTC (Real Time Clock), this library does not support date and time nor does the megaAVR 0-series MCU has such hardware support.
An external 32.768 kHz crystal can be used or the on-chip 32.768 kHz ultra low power (ULP) oscillator albeit less accurate are supported.
A resolution of 1 s is provided with alarm period up to 2^16 = 65536 seconds (more than 18 hours).
This library can be used in conjuction with the LowPowerAVRZero library for complete low power application with megaAVR 0-series MCU.
