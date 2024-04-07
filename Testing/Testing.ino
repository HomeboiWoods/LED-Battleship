#include <FastLED.h>

#define LED_PIN3     3
#define LED_PIN4     4
#define LED_PIN5     5
#define LED_PIN6     6
#define LED_PIN7     7
#define LED_PIN8     8
#define LED_PIN9     9
#define LED_PIN10    10
#define LED_PIN11    11
#define NUM_LEDS    9   // 9 rows x 9 columns
#define BRIGHTNESS  100  // LED brightness



#define BUTTON_UP_PIN    A0  // Pin for the UP button
#define BUTTON_DOWN_PIN  A1  // Pin for the DOWN button
#define BUTTON_LEFT_PIN  A2  // Pin for the LEFT button
#define BUTTON_RIGHT_PIN A3  // Pin for the RIGHT button

#define COLOR_ON    CRGB::White   // Color when LED is ON
#define COLOR_OFF   CRGB::Maroon   // Color when LED is OFF

CRGB leds[NUM_LEDS][NUM_LEDS];

int currentRow = 0; // Initial row index
int currentCol = 0; // Initial column index

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN3, GRB>(leds[0], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN4, GRB>(leds[1], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN5, GRB>(leds[2], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN6, GRB>(leds[3], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN7, GRB>(leds[4], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN8, GRB>(leds[5], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN9, GRB>(leds[6], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN10, GRB>(leds[7], NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN11, GRB>(leds[8], NUM_LEDS);
  
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize button pins as INPUT with pull-up resistors
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
}

void loop() {
  // Move the LED based on button presses
  if (digitalRead(BUTTON_UP_PIN) == LOW && currentCol > 0) {
    currentCol--;
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_DOWN_PIN) == LOW && currentCol < 8) {
    currentCol++;
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_LEFT_PIN) == LOW && currentRow > 0) {
    currentRow--;
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW && currentRow < 8) {
    currentRow++;
    delay(200); // Button debounce delay
  }

  // Light up the current LED
  lightUpLED(currentRow, currentCol);
}

// Function to light up the LED at given row and column
void lightUpLED(int row, int col) {
  // Turn off all LEDs
  FastLED.clear();
  // Turn on the specified LED
  leds[currentRow][currentCol] = COLOR_ON;

  // Show the LEDs
  FastLED.show();
}