
#define BUTTON_UP_PIN    51  // Pin for the UP button
#define BUTTON_DOWN_PIN  41  // Pin for the DOWN button
#define BUTTON_LEFT_PIN  50  // Pin for the LEFT button
#define BUTTON_RIGHT_PIN 52  // Pin for the RIGHT button

int currentRow1 = 0; // Initial row index
int currentCol1 = 0; // Initial column index


void setup() {
  // Initialize button pins as INPUT with pull-up resistors
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);

  // Initalize the serial monitor
  Serial.begin(9600);
}


void loop() {
  bool updated = false;

  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    currentRow1++;
    updated = true;
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    currentRow1--;
    updated = true;
    delay(200); // Button debounce delay
  } 

  if (digitalRead(BUTTON_LEFT_PIN) == LOW) {
    currentCol1--;
    updated = true;
    delay(200); // Button debounce delay
  } else if (digitalRead(BUTTON_RIGHT_PIN) == LOW) {
    currentCol1++;
    updated = true;
    delay(200); // Button debounce delay
  }

  if (updated) {
    Serial.print("Current Row: ");
    Serial.print(currentRow1);
    Serial.print(", Current Col: ");
    Serial.println(currentCol1);
  }
}