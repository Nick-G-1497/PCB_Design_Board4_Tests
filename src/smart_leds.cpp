#include <Adafruit_NeoPixel.h>


#define SMART_LED_PIN 7
#define NUMPIXELS 4

#define DELAYVAL 5
int red;
int blue;
int green;

static bool fade_up = true;

Adafruit_NeoPixel pixels(NUMPIXELS, SMART_LED_PIN, NEO_GRBW + NEO_KHZ800);

void init_smart_leds()
{
	pixels.begin();
	red = 25;
	blue = 100;
	green = 200;
}


int fade(int value)
{
  if ( value  == 255 )
  {
	  fade_up = false;
  }

  if (value == 0 )
  {
	  fade_up = true;
  }


  // Serial.println(value);
  if (fade_up)
  {
	return value + 1;
  }
  return value - 1;  

}
void update_smart_leds ()
{
	pixels.clear();

	//red = fade(red);
        //blue = fade (blue);
        green = fade (green);

	for (int i = 0; i < NUMPIXELS; i++){
	//	red = fade (red);
	//	blue = fade (blue);
	//	green = fade (green);


		pixels.setPixelColor(i, pixels.Color(red, green, blue));
		pixels.show();
		// delay(DELAYVAL);
	}
	delay(DELAYVAL);
}



