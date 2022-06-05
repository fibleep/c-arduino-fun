### MUSIC PLAYER
## made by Filip Nowak

--> UNFINISHED <--

LIBRARIES USED:
timer.h
music_player.h
buzzer.h
display.h
leds.h

BUTTON 1->PREVIOUS SONG
BUTTON 2(PRESS)->GO BACK
BUTTON 2(CLICK)->CHOOSE SONG
BUTTON 2(CLICK)->PAUSE/PLAY SONG
BUTTON 3->NEXT SONG

The user is able to choose from 3 different songs, once button 2 is clicked the song will start playing.
TIMER and SONG NAME are documented in the serial monitor

The program uses interrupts to move between screens and time the songs, the timer is only printed when the song isnt paused

