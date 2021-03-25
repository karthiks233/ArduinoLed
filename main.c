#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
int audio = A0;
int k = 255;
int dce = 0;
int dce_check = 0;
long p_check= 0;
long rch_check = 0;
long pst_rch_check = 0;
int running_speed = 3;

void setup() {
 delay( 3000 );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

 
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB(0, 0, 0);
  FastLED.show();
  pinMode(audio, INPUT);

}

void loop()
{
  int audio_input = analogRead(audio);

  if (audio_input > 0)
  {
    p_check= ((long)NUM_LEDS * (long)(audio_input*2)) / 1023L;

    if (p_check> rch_check)
      rch_check = p_check;

   
  }

  clrsplash();

  k = k - running_speed;
  if (k < 0)
    k = 255;

 
  dce_check++;
  if (dce_check > dce)
  {
    dce_check = 0;
    if (rch_check > 0)
      rch_check--;
  }
 
}
void clrsplash()
{
  for(int i = NUM_LEDS - 1; i >= 0; i--) { 
    if (i < rch_check)
      leds[i] = rncolr((i * 256 / 50 + k) % 256); 
    else
      leds[i] = CRGB(0, 0, 0);      
  }
  FastLED.show();
}
CRGB rncolr(int pos) {
  CRGB color (0,0,0);
  if(pos < 85) {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f; 
    color.b = 255 - color.r;
  } else if(pos < 170) {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  } else if(pos < 256) {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 1;
  }
  return color;
}
