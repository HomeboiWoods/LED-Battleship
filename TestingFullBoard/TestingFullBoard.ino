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

#define BRIGHTNESS  10  // LED brightness

#define BUTTON_UP_PIN    0  // Pin for the UP button
#define BUTTON_DOWN_PIN  1  // Pin for the DOWN button
#define BUTTON_LEFT_PIN  11  // Pin for the LEFT button
#define BUTTON_RIGHT_PIN 12  // Pin for the RIGHT button

#define BUTTON_SELECT 13 // Pin for the SELECT button

#define COLOR_ON    CRGB::White   // Color when LED is ON
#define COLOR_OFF   CRGB::Red   // Color when LED is OFF

CRGB leds[9][NUM_LEDS];

int currentRow = 0; // Initial row index
int currentCol = 0; // Initial column index

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

  FastLED.setBrightness(BRIGHTNESS);

  // Initialize button pins as INPUT with pull-up resistors
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  lightUpLED(currentRow, currentCol); 
}

// LEDs begin at 
void loop() {
  // Move the LED based on button presses
  if (digitalRead(BUTTON_UP_PIN) == LOW && currentRow < 8) {
    currentRow++;
    lightUpLED(currentRow, currentCol); 
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_DOWN_PIN) == LOW && currentRow > 0) {
    currentRow--;
    lightUpLED(currentRow, currentCol);
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_LEFT_PIN) == LOW && currentCol > 0) {
    currentCol--;
    lightUpLED(currentRow, currentCol);
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW && currentCol < 8) {
    currentCol++;
    lightUpLED(currentRow, currentCol);
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_SELECT) == LOW) {
    lightUpLEDBlue(currentRow, currentCol);
    delay(200); // Button debounce delay
  }

  // Light up the current LED
  
}

// Function to light up the LED at given row and column
void lightUpLED(int row, int col) {
  // Turn off all LEDs
  FastLED.clear();
  for(int i=0; i<9;++i){
    for(int j=0;j<9;++j){
        leds[i][j]=COLOR_OFF;
        if((i==currentRow)&&(j==currentCol)){
          leds[i][j]=COLOR_ON;
        }
    }
  }
  // Turn on the specified LED


  // Show the LEDs
  FastLED.show();
  }

  // Function to light up the LED at given row and column and turn it blue
void lightUpLEDBlue(int row, int col) {
  // Turn off all LEDs
  FastLED.clear();
  for(int i=0; i<9;++i){
    for(int j=0;j<9;++j){
        leds[i][j]=COLOR_OFF;
        if((i==currentRow)&&(j==currentCol)){
          leds[i][j].b=221;
        }
    }
  }
  // Turn on the specified LED


  // Show the LEDs
  FastLED.show();
  }