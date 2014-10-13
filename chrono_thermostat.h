// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _room_thermostat_H_
#define _room_thermostat_H_
#include "Arduino.h"
//add your includes for the project room_thermostat here
#include "Wire.h"
#include "DS1307RTC.h"
#include "idDHT11.h"
#include "Time.h"
#include "U8glib.h"
#include <SPI.h>
#include <SD.h>




//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project room_thermostat here

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message


/*  code to process time sync messages from the serial port
 *
 * to setup date and time send via Serial the UTC 11 digits followed by T
 *
 *   */

time_t processSyncMessage() {  /*  code to process time sync messages from the serial port   */

	// return the time if a valid sync message is received on the serial port.
  while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of a header and ten ascii digits
    char c = Serial.read() ;
    Serial.print(c);
    if( c == TIME_HEADER ) {
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){
        c = Serial.read();
        if( c >= '0' && c <= '9'){
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number
        }
      }
      return pctime;
    }
  }
  return 0;
}






//Do not add code below this line
#endif /* _room_thermostat_H_ */
