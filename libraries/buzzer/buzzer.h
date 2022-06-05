#include <util/delay.h>
#include <ctype.h>
#include <avr/io.h>

void enableBuzzer();
void playTone( float frequency, uint32_t duration);