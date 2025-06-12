#include <Adafruit_CircuitPlayground.h>

// Game settings
#define TOTAL_TURNS 11 //Number of rounds per game (0–10, i.e. 11 turns)
const int LEVELS = 3; //for each of the levels
const int TURNS_PER_LEVEL[LEVELS] = {4, 3, 3};  // 4 turns @ 2.0s, 3 @ 1.5s, 3 @ 1.0s
const float LEVEL_TIMES[LEVELS] = {2.0, 1.5, 1.0};
const float SHAKE_THRESHOLD = 12.0;  // Adjust for sensitivity

// Game variables
int score = 0;//Track progress
int turn = 0;
int currentLevel = 0; 
bool gameActive = false; //Whether the game is running
unsigned long colorStartTime; //Timestamp when the LED color was shown, used for long periods of time
int currentColor;  // 0=green, 1=red, 2=yellow

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
}

void loop() {
  // Start game when any button is pressed
  if (!gameActive) {
    if (CircuitPlayground.leftButton() || CircuitPlayground.rightButton()) {
      startGame();
      delay(200); // avoids double triggers
    }
    return;
  }

  // if the turns are done end the game
  if (turn >= TOTAL_TURNS) {
    endGame();
    return;
  }

  // Check if still in current turn's display time
  if (millis() - colorStartTime < LEVEL_TIMES[currentLevel] * 1000) { //how much time has passed subtracted by how much time is given
    checkPlayerInput();
  } else {
    // Time's up - move to next turn
    nextTurn();
  }
}
//starting up the game
void startGame() {
  gameActive = true;
  score = 0;
  turn = 0;
  currentLevel = 0;
  
  // countdown animation
  for (int i = 0; i < 3; i++) {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(i, 255, 255, 0); // Yellow
    delay(500);
  }
  CircuitPlayground.clearPixels(); //clear the board
  delay(300);
  
  nextTurn(); // start the first turn
}
//goes to the next turn until it reaches 10 turns
void nextTurn() {
  if (turn >= TOTAL_TURNS) {
    return;
  }

  // Check for level transition
  int newLevel = 0;
  int turnsSoFar = 0;
  for (int i = 0; i < LEVELS; i++) {
    turnsSoFar += TURNS_PER_LEVEL[i]; //count the turns each level takes and if is within the black we stay
    if (turn < turnsSoFar) {
      newLevel = i; // 
      break;
    }
  }

  if (newLevel != currentLevel) { //if we cross into a new level we update
    currentLevel = newLevel;
  }

  // Choose random color
  currentColor = random(3); // choose a random color
  showColor(currentColor);
  colorStartTime = millis(); //remember when we showed the color

  
  turn++; // add to the turn counter
}

void showColor(int color) {
  CircuitPlayground.clearPixels();
  uint32_t c;
  
  switch(color) {
    case 0: c = CircuitPlayground.strip.Color(0, 255, 0); break;   // Green
    case 1: c = CircuitPlayground.strip.Color(255, 0, 0); break;   // Red
    case 2: c = CircuitPlayground.strip.Color(255, 255, 0); break; // Yellow
  }
  
  for (int i = 0; i < 10; i++) { // light all 10 LED's in that color
    CircuitPlayground.setPixelColor(i, c);
  }
}

void checkPlayerInput() {
  bool correct = false;
  // check if the input was proper
  switch(currentColor) {
    case 0: // Green - left button
      if (CircuitPlayground.leftButton()) correct = true;
      break;
    case 1: // Red - right button
      if (CircuitPlayground.rightButton()) correct = true;
      break;
    case 2: // Yellow - shake
      if (abs(CircuitPlayground.motionX()) > SHAKE_THRESHOLD || 
          abs(CircuitPlayground.motionY()) > SHAKE_THRESHOLD || 
          abs(CircuitPlayground.motionZ()) > SHAKE_THRESHOLD) {
        correct = true;
      }
      break;
  }

  if (correct) {
    score++;
    flashFeedback(true); //flash green for correct
    nextTurn();
  } 
  else if ((currentColor != 2) && // Only check buttons for green/red
           ((currentColor == 0 && CircuitPlayground.rightButton()) || 
            (currentColor == 1 && CircuitPlayground.leftButton()))) {
    flashFeedback(false); //flash red for incorrect
    nextTurn();
  }
}

void flashFeedback(bool correct) {
  uint32_t color = correct ? CircuitPlayground.strip.Color(0, 255, 0) : // Green for correct
                            CircuitPlayground.strip.Color(255, 0, 0);   // Red for incorrect
  for (int i = 0; i < 10; i++) { // goes over all the pixels
    CircuitPlayground.setPixelColor(i, color); // pixel, color
  }
  delay(300);
  CircuitPlayground.clearPixels();
}

void endGame() { // turn off the game
  gameActive = false;
  
  // Display score with blue LEDs
  CircuitPlayground.clearPixels();
  
  // Show animation for score display
  for (int i = 0; i < min(score, 10); i++) {
    CircuitPlayground.setPixelColor(i, 0, 0, 255); //setting the pizels to blue
    delay(150);
  }
  
  delay(2000);
  CircuitPlayground.clearPixels();
}