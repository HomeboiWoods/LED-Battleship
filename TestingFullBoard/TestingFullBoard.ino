#include <FastLED.h>

#define LED_PIN1     2
#define LED_PIN2     3
#define LED_PIN3     4
#define LED_PIN4     5
#define LED_PIN5     6
#define LED_PIN6     7
#define LED_PIN7     8
#define LED_PIN8     9
#define LED_PIN9     10
#define NUM_LEDS     9 // Change this to the number of LEDs in your strip

CRGB leds[9][NUM_LEDS];

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds[0], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds[1], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(leds[2], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(leds[3], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN5, GRB>(leds[4], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN6, GRB>(leds[5], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN7, GRB>(leds[6], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN8, GRB>(leds[7], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN9, GRB>(leds[8], NUM_LEDS);
}

void loop() {
  // Turn on all LEDs with a color (for example, red)
  for(int i = 0; i < NUM_LEDS; i++) {
    for(int j=0;j<NUM_LEDS;++j){

        leds[i][j] = CRGB::Red;
    }
  }

  // Update the LED strip
  FastLED.show();

  // A delay to see the change
  delay(1000);

  // Optional: turn off all LEDs
  for(int i = 0; i < NUM_LEDS; i++) {
    for(int j=0;j<NUM_LEDS;++j){

    leds[i][j] = CRGB::Black;
    }
  }
  FastLED.show();
  delay(1000);
}