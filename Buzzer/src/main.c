#define __DELAY_BACKWARD_COMPATIBLE__
#include <leds.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <buzzer.h>

//DURATION IS IN MILLISECONDS
#define DURATION 250

//FREQUENCIES OF THE NOTES
#define C5  523.250
#define D5  587.330
#define E5  659.250
#define F5  698.460
#define G5  783.990
#define A5  880.00
#define B5  987.770
#define C6  1046.500

int main()
{
    initUSART();
    uint32_t frequencies[] = { C5, D5, E5, F5, G5, A5, B5, C6 };    //do-re-mi...
    enableBuzzer();
    enableOneLed( 0 );
    lightDownOneLed( 0 );
    while ( 1 )
    {
        for ( int note = 0; note < 8; note++ )
        {
            playTone( frequencies[note], DURATION );
            printf( "Period: %lu\n", frequencies[ note ] );
            lightUpOneLed( 0 );
            _delay_ms( DURATION );
            lightDownOneLed( 0 );
        }
    }
    return 0;
}