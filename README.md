# freETarget minimalistic

This is a fork from the forked minimalistic version. The aim is to build a version based on widely available parts only, with electronics cost of less than 30 USD. I have added an LM335 temperature sensor, and altitude compensation. 

## What is frETagret minimalistic ##

This version requires only the following electronics parts which you can source directly from you provider of choice:

**1x Arduino mega 2560**
**4x KY-037 microphone units**
**LM335 temp sensor**

This is possible due to a software change, which takes full advantage of the ATmega2560 capabilities. In the original version, shot timing is achieved using external timing infrastructure. The ATmega2560 has 6 timers, with 4 of them offering an Input Capture Unit (ICU). Using this mode, the timer values are immediately stored when a pin changes and an interrupt is fired, so there is no software jitter. One of the hurdles to overcome is in the design of the Arduino mega board, which does not connect all the ICU pins to the headers. This was overcome by bridging the respective to pins to adjacent fee ones with a fine-tipped soldering iron:

**Bridge PD4, PD5, PD6 and PD7**

**Bridge PE5, PE6, PE7**

Once done, connect the digital outputs of the microphone boards as follows:

**North: pin 38, East: pin 3, South: pin 49, West: pin 48**
**Vcc and GND to the respective Arduino pins**


**LM335 is added to A1 and GND (can use reset switch ground)**
Internal pullup is used for A1. 


For the mics to trigger all at the same level, set the pot voltage to a value of your finding (e.g. 0.380 V in my case).

Please refer to the original software for full building instructions.

A word to accuracy and precision of this version. I have not fully specified these parameters. While the timers work without a jitter (this vas verified and confirmed), there might be a diminished performance based on the selected microphone boards. Temperature sensor added back. 


