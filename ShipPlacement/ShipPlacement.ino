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
#define COLOR_SHIP   CRGB::Blue // Color of LED where ships are
#define COLOR_GREEN CRGB(0, 255, 0) // Full green

// Create enumerations of the different ships
enum Ship { NONE, SHIP1, SHIP2, SHIP3, SHIP4 };

// Create enumerations of the different orentation states
enum Orientation { HORIZONTAL_LEFT,  HORIZONTAL_RIGHT, VERTICAL_UP, VERTICAL_DOWN};

// Create enumerations of the different game states
enum GameState { SELECTING_LOCATION, SELECTING_ORIENTATION, PLACING_SHIP };


// Set the current values of our enumerations for use
// These are global variables so they can be used in functions later
Ship currentShip = SHIP1;
Orientation currentOrientation = HORIZONTAL_LEFT;
GameState currentState = SELECTING_LOCATION;

bool gameEnded = false;

CRGB leds[9][NUM_LEDS];

int currentRow = 0; // Initial row index
int currentCol = 0; // Initial column index

bool grid[9][NUM_LEDS]; // 2D array representing the LED grid


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
    lightUpLED(currentRow, currentCol, currentOrientation); 

    memset(grid, 0, sizeof(grid)); // Initialize grid array to false/0
}

// LEDs begin at 
void loop() {

    if (gameEnded) {
        return;
    }
    // Handle game state transitions and actions
    switch(currentState) {
        case SELECTING_LOCATION:
            handleMovement();
            // Highlight the current LED to indicate potential starting point of the ship
            lightUpLED(currentRow, currentCol, currentOrientation);
            break;

        case SELECTING_ORIENTATION:
            // Change orientation with button presses (left/right can toggle orientation)
            // Implement a function to handle this (not provided in your code)
            handleOrientationChange();
            lightUpLED(currentRow, currentCol, currentOrientation);
            break;

        case PLACING_SHIP:
            // Place the ship on the grid
            placeShip();
            // Go to the next ship or state after placing
            // Implement logic to advance to the next ship or next game phase
            advanceToNextShipOrState();
            break;
    }

    // Handle select button actions - this might need to be moved or adjusted
    // based on how you want to trigger state transitions
    handleSelection();
}

// Function to light up the LED at given row and column based on game state
void lightUpLED(int row, int col, Orientation orientation) {
    // Clear only the current LED, keeping the state of other LEDs intact
    FastLED.clear();
    updateLEDsBasedOnGrid();

    if (currentState == SELECTING_LOCATION) {
        // Light up the current LED to a different color to show selection
        leds[row][col] = COLOR_ON; 
    } else if (currentState == SELECTING_ORIENTATION) {
        // Light up LEDs in a line based on the ship's orientation and length
        int shipLength = getShipLength(currentShip);

        if (currentState == SELECTING_ORIENTATION) {
            // Handle all four orientations
            switch (orientation) {
                case HORIZONTAL_LEFT:
                    for (int i = col; i >= col - shipLength + 1 && i >= 0; i--)
                        leds[row][i] = COLOR_ON;
                    break;
                case HORIZONTAL_RIGHT:
                    for (int i = col; i < col + shipLength && i < NUM_LEDS; i++)
                        leds[row][i] = COLOR_ON;
                    break;
                case VERTICAL_UP:
                    for (int i = row; i >= row - shipLength + 1 && i >= 0; i--)
                        leds[i][col] = COLOR_ON;
                    break;
                case VERTICAL_DOWN:
                    for (int i = row; i < row + shipLength && i < 9; i++)
                        leds[i][col] = COLOR_ON;
                    break;
            }
        }
    }
    FastLED.show(); // Update LEDs
}

// Add this function to handle orientation change
void handleOrientationChange() {
    int shipLength = getShipLength(currentShip);

    if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
        // Check if ship will go off-grid on the left
        if(currentCol - shipLength + 1 >= 0)
            currentOrientation = HORIZONTAL_LEFT;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
        // Check if ship will go off-grid on the right
        if(currentCol + shipLength <= NUM_LEDS)
            currentOrientation = HORIZONTAL_RIGHT;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_UP_PIN) == LOW) {
        // Check if ship will go off-grid on the top
        if(currentRow - shipLength + 1 >= 0)
            currentOrientation = VERTICAL_UP;
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
        // Check if ship will go off-grid on the bottom
        if(currentRow + shipLength <= 9)
            currentOrientation = VERTICAL_DOWN;
        delay(200); // Button debounce delay
    }
}

void handleMovement() {
    // Move the LED based on button presses
    if (digitalRead(BUTTON_UP_PIN) == LOW && currentRow < 8) {
        currentRow++;
        lightUpLED(currentRow, currentCol, currentOrientation); 
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_DOWN_PIN) == LOW && currentRow > 0) {
        currentRow--;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_LEFT_PIN) == LOW && currentCol > 0) {
        currentCol--;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW && currentCol < 8) {
        currentCol++;
        lightUpLED(currentRow, currentCol, currentOrientation);
        delay(200); // Button debounce delay
    }
}

void handleSelection() {
    if (digitalRead(BUTTON_SELECT) == LOW) {
        delay(200); // Button debounce delay

        if (currentState == SELECTING_LOCATION) {
            currentState = SELECTING_ORIENTATION;
        } else if (currentState == SELECTING_ORIENTATION) {
            currentState = PLACING_SHIP;
            // Move to the next ship or player
        }
    }
}

int getShipLength(Ship ship) {
    // Use a switch statement to return the length of our ship depending which one it is
    switch (ship) {
        case SHIP1: return 5;
        case SHIP2: return 4;
        case SHIP3: return 3;
        case SHIP4: return 2;
        default: return 0;
    }
}

void placeShip() {
    int shipLength = getShipLength(currentShip);

    // Place the ship on the grid based on the current orientation
    switch (currentOrientation) {
        case HORIZONTAL_LEFT:
            for (int i = 0; i < shipLength; ++i) {
                grid[currentRow][currentCol - i] = true;
            }
            break;
        case HORIZONTAL_RIGHT:
            for (int i = 0; i < shipLength; ++i) {
                grid[currentRow][currentCol + i] = true;
            }
            break;
        case VERTICAL_UP:
            for (int i = 0; i < shipLength; ++i) {
                grid[currentRow - i][currentCol] = true;
            }
            break;
        case VERTICAL_DOWN:
            for (int i = 0; i < shipLength; ++i) {
                grid[currentRow + i][currentCol] = true;
            }
            break;
    }

    // Optionally, update LED display here or elsewhere after placement
    updateLEDsBasedOnGrid();
}

void updateLEDsBasedOnGrid() {
    FastLED.clear();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < NUM_LEDS; ++j) {
            // Set the LED color to blue if a ship is placed on the grid location
            leds[i][j] = grid[i][j] ? COLOR_SHIP : COLOR_OFF;
        }
    }
    FastLED.show();
}

void advanceToNextShipOrState() {
    // Check if the current ship is the last one
    if (currentShip == SHIP4) {
        /*
        // If it is the last ship, transition to the next phase of the game
        // This might involve setting up for the next player's turn or starting the battle phase
        // For now, let's just reset to the initial state
        currentState = SELECTING_LOCATION;
        currentShip = SHIP1; // Reset to first ship for next player or next round
        // Add any additional logic for transitioning to the next game phase here
        */

        // For DEMO, show the ships at the end and turn all colors to GREEN
        FastLED.clear();
        for(int i=0; i<9;++i){
            for(int j=0;j<9;++j){
                leds[i][j]= COLOR_GREEN;
            }
        }
        FastLED.show();

        delay(1000);

        // Finally, display all ships
        updateLEDsBasedOnGrid();

        // End game for demo purposes
        currentShip = NONE;
        gameEnded = true;
    } else {
        // If it is not the last ship, move to the next ship
        currentShip = static_cast<Ship>(static_cast<int>(currentShip) + 1);
        // Reset to SELECTING_LOCATION state for the next ship
        currentState = SELECTING_LOCATION;
    }

    // Reset row and column index to start position for next ship placement
    currentRow = 0;
    currentCol = 0;
}