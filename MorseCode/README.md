### MORSE CODE
## made by Filip Nowak

LIBRARIES USED:

leds.h --> toMorse() 

the user passes a string and the function converts it to morse code.

firstly it counts down, and then with intervals of:

-- a dot lasts for one second
-- a dash last for three seconds
-- the space between dots and dashes that are part of the same letter is one second
-- the space between different letters is three seconds
-- the space between different words is seven seconds

there's a for loop which iterates through the string and depending on the letter, it flashes with different patterns of dots and dashes.

