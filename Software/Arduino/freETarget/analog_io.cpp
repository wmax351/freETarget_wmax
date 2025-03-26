/*-------------------------------------------------------
 * 
 * analog_io.ino
 * 
 * General purpose Analog driver
 * 
 * ----------------------------------------------------*/

#include "Arduino.h"
#include "freETarget.h"
#include "analog_io.h"
#include "Wire.h"
#include "diag_tools.h"

// Function declarations
void init_analog_io(void);
void set_LED_PWM_now(int new_LED_percent);
void set_LED_PWM(int new_LED_percent);
unsigned int revision(void);
double temperature_C(void);


/*----------------------------------------------------------------
 * 
 * function: init_analog()
 * 
 * brief: Initialize the analog I/O
 * 
 * return: None
 * 
 *--------------------------------------------------------------*/
void init_analog_io(void)
{
  if ( DLT(DLT_CRITICAL) )                  // and not in trace mode (DIAG jumper installed)
  {
    Serial.print(T("init_analog_io()"));// Blink the LEDs
  }
  
  pinMode(LED_PWM, OUTPUT);
  pinMode(A1, INPUT_PULLUP);
  return;
}

/*----------------------------------------------------------------
 * 
 * function: set_LED_PWM()
 * function: set_LED_PWM_now()
 * 
 * brief: Program the PWM value
 * 
 * return: None
 * 
 *----------------------------------------------------------------
 *
 * json_LED_PWM is a number 0-100 %  It must be scaled 0-255
 * 
 * The function ramps the level between the current and desired
 * 
 *--------------------------------------------------------------*/
static unsigned int old_LED_percent = 0;

void set_LED_PWM_now
  (
  int new_LED_percent                            // Desired LED level (0-100%)
  )
{
  if ( new_LED_percent == old_LED_percent )
  {
    return;
  }
  
  if ( DLT(DLT_DIAG) )
  {
    Serial.print(T("new_LED_percent:")); Serial.print(new_LED_percent); Serial.print(T("  old_LED_percent:")); Serial.print(old_LED_percent);
  }

  old_LED_percent = new_LED_percent;
  analogWrite(LED_PWM, old_LED_percent * 256 / 100);  // Write the value out
  
  return;
}
  

void set_LED_PWM                                  // Theatre lighting
  (
  int new_LED_percent                            // Desired LED level (0-100%)
  )
{
  if ( DLT(DLT_DIAG) )
  {
    Serial.print(T("new_LED_percent:")); Serial.print(new_LED_percent); Serial.print(T("  old_LED_percent:")); Serial.print(old_LED_percent);
  }

/*
 * Special case, toggle the LED state
 */
  if (new_LED_percent == LED_PWM_TOGGLE)
  {
    new_LED_percent = 0;
    if ( old_LED_percent == 0 )
    {
      new_LED_percent = json_LED_PWM;
    }
  }
  
/*
 * Loop and ramp the LED  PWM up or down slowly
 */
  while ( new_LED_percent != old_LED_percent )  // Change in the brightness level?
  {
    analogWrite(LED_PWM, old_LED_percent * 256 / 100);  // Write the value out
    
    if ( new_LED_percent < old_LED_percent )
    {
      old_LED_percent--;                        // Ramp the value down
    }
    else
    {
      old_LED_percent++;                        // Ramp the value up
    }

    delay(ONE_SECOND/50);                       // Worst case, take 2 seconds to get there
  }
  
/*
 * All done, begin the program
 */
  if ( new_LED_percent == 0 )
  {
    digitalWrite(LED_PWM, 0);
  }
  return;
}

/*----------------------------------------------------------------
 * 
 * function: revision(void)
 * 
 * brief: Return the board revision
 * 
 * return: Board revision level
 * 
 *--------------------------------------------------------------*/
  
unsigned int revision(void)
{
  return REV_300;
}

/* temp sensor with LM335
*/

double temperature_C(void)
{
  // Function implementation here
  int rawValue = analogRead(LM335_ANA); // Read the analog value from the LM335
  double voltage = (rawValue / 1023.0) * 5.0; // Convert the raw value to voltage (assuming 5V reference)
  double temperature = (voltage - 2.73) * 100.0; // Convert voltage to temperature in Celsius
  return temperature;

}

