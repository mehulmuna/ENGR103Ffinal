This reaction game for the Circuit Playground Express begins when the player presses Button A. During the game, LEDs will light up in green, red, or yellow. Players must respond correctly: press the left button for green, the right button for red, and scream for yellow (detected by the sound sensor). Each correct action earns 1 point, while incorrect actions yield no points. The game progresses through three speed levels—1.5 seconds, 1.0 second, and 0.5 seconds—changing every 5 turns, and concludes after 15 total turns.

| Input                          | Description                              | CPX Method                        |
|-------------------------------|------------------------------------------|-----------------------------------|
| Green LED shown               | Player must press **Left Button**        | `CircuitPlayground.leftButton()`  |
| Red LED shown                 | Player must press **Right Button**       | `CircuitPlayground.rightButton()` |
| Yellow LED shown              | Player must **Scream**                   | `CircuitPlayground.soundSensor()` |
| Button A pressed              | Starts the game                          | `CircuitPlayground.buttonA()`     |

| Output                         | Description                              | CPX Method                        |
|-------------------------------|------------------------------------------|-----------------------------------|
| LED lights up (Green/Red/Yellow) | Visual cue for reaction game           | `setPixelColor(index, color)`     |
| Score displayed (optional)    | Points could be displayed with tone/LEDs | `show()`, `playTone()` etc.       |
