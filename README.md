## Game Concept
This is a color-based reaction game for the Circuit Playground Express. The game starts when the player presses any button. LEDs will randomly light up red, green, or yellow. The player must respond by pressing the **left button** for green, the **right button** for red, or **shaking the device** for yellow. Correct responses earn +1 point; incorrect responses earn 0. The game progresses in speed: 4 turns at 2.0 seconds, 3 turns at 1.5 seconds, and 3 turns at 1.0 second per cue, totaling 10 turns. At the end, the number of **blue LEDs** displayed corresponds to the final score.

## Input/Output Table

| Input Trigger         | Expected Player Action       | CPX Method                          |
|-----------------------|------------------------------|-------------------------------------|
| Green LED appears     | Press **Left Button**        | `CircuitPlayground.leftButton()`    |
| Red LED appears       | Press **Right Button**       | `CircuitPlayground.rightButton()`   |
| Yellow LED appears    | **Shake** the board          | `CircuitPlayground.motionX/Y/Z()`   |
| Any button pressed    | Start the game               | `CircuitPlayground.leftButton()` or `rightButton()` |

| Output Trigger         | Description                              | CPX Method                          |
|------------------------|------------------------------------------|-------------------------------------|
| LED lights up (color)  | Show green, red, or yellow signal        | `CircuitPlayground.setPixelColor()` |
| Blue LEDs at end       | Display score with number of blue pixels | `setPixelColor(i, blue)` + loop     |
