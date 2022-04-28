#include <avr/io.h>

void enableOneLed(int);

void enableMultipleLeds(uint8_t); 

void enableAllLeds ();

void lightUpOneLed(int); 

void lightUpMultipleLeds (uint8_t);

void lightUpAllLeds (); 

void lightDownOneLed(int); 

void lightDownMultipleLeds (uint8_t);

void lightDownAllLeds (); 

void lightToggleOneLed(int);

void fadeInLed(int,int);

void lightUpInOrder();

void ledCountdown();

void flashLed(int,int);

void CHAOS();

void walkThroughSequence();

void stringLightUp(char[]);

void toMorse(char[]);
void dot();
void dash();

void ledDancing(int);

void ledDancingRevers(int);

int isOn(int);

void playPuzzle(uint8_t[],int);