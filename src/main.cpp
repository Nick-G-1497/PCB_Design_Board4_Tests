#include <Wire.h>
#include <Arduino.h>
#include "dht11.h"
#include "music.h"
#include "hall_effect.h"
#include "smart_leds.h"
#include "sinewave.h"


// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire


void setup() {
  Wire.begin();

  Serial.begin(115200);
  while (!Serial)
     delay(10);

#ifdef MUSIC
   	play_song();
#endif


#ifdef SMART_LEDS
	Serial.println("===========================");
	Serial.println(" -- Smart LED Demo");
	Serial.println("===========================");	       
	init_smart_leds();
#endif


#ifdef SINE
	setup_sinewave();
#endif

#ifdef HALL_EFFECT

	setup_hall_effect();

#endif

#ifdef SCAN
	  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
#endif
}  
  
  
void loop() {

#ifdef SMART_LEDS

	update_smart_leds();
#endif

#ifdef HALL_EFFECT

	read_magnetic_field();
#endif


#ifdef SINE
	sinewave();
#endif


#ifdef TEMP
	read_DHT11();
	delay(10000);
#endif
}



