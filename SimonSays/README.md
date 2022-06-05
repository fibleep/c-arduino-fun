### SIMON SAYS
## made by Filip Nowak

LIBRARIES USED:
buttons.h --> generatePuzzle()
buttons.h --> printPuzzle()
leds.h --> playPuzzle()

The 4th led is going to flash until the user presses a button.
then, it's going to countdown from 4 indicating the beginning of the game.
after the first button press, any input is disabled until the sequence is over.

once there's no lights the user can input a series of buttons, if the button pressed is correct the 4th led starts flashing, otherwise the sequence repeats itself.

once the user correctly inputs all 10 sequences, the game is over.


