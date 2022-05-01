// to allow variables as parameter for the _delay-functions (must be placed before the include of delay.h)
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#define NUMBER_OF_LEDS 4 // Define is a "preprocessor directive". It ensures that every NUMBER_OF_LEDS will be replaced by 4 in the following code
#define DELAY 2000

void enableOneLed(int lednumber) // C has no classes; functions can be included directly in the .c file.
{
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1)
        return;
    DDRB |= (1 << (PB2 + lednumber)); // Check the tutorial "Writing to a Pin". We know from the documentation on
                                      // the multifunctional shield that the LEDs start at PB2
}
void enableMultipleLeds(uint8_t mask)
{
    DDRB |= (mask << PB2);
}
void enableAllLeds()
{
    for (int i = 0; i < 4; i++)
    {
        enableOneLed(i);
    }
    lightDownAllLeds();
}
void lightUpLed(int lednumber) // Note: enabled LEDs light up immediately ( 0 = on )
{
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1)
        return;
    enableOneLed(lednumber);
    PORTB &= ~(1 << (PB2 + lednumber)); // Check the tutorial on "Bit Operations" to know what happens in this line.
}
void lightUpAllLeds()
{
    PORTB &= ~(0b00001111 << PB2);
}
void lightDownLed(int lednumber)
{
    if (lednumber < 0 || lednumber > 3)
        return;
    PORTB |= (1 << (PB2 + lednumber)); // Make sure you understand this line as well!
}
void lightDownMultipleLeds(uint8_t mask)
{
    PORTB |= (mask << PB2);
}
void lightDownAllLeds()
{
    PORTB |= (0b00001111 << PB2);
}
/**
 * @brief toggle one led
 *
 * @param led
 */
void lightToggleOneLed(int led)
{
    if (led < 0 || led > NUMBER_OF_LEDS - 1)
        return;
    enableOneLed(led);
    PORTB ^= (1 << (PB2 + led));
}
/**
 * @brief dim a led
 *
 * @param lednumber
 * @param percentage
 * @param duration
 */
void dimLed(int lednumber, int percentage, int duration)
{
    enableOneLed(lednumber);
    double time = percentage / 100.0;
    for (int i = 0; i < duration; i++)
    {
        lightUpLed(lednumber);
        _delay_ms(time);
        lightDownLed(lednumber);
        _delay_ms(1.0 - time);
    }
}
/**
 * @brief fade in a led
 *
 * @param led
 * @param duration
 */
void fadeInLed(int led, int duration)
{
    enableOneLed(led);
    double timeOn = 100.0;
    double timeOff = 0.0;
    for (int i = 0; i < duration; i++)
    {
        lightUpLed(led);
        _delay_ms(timeOn);
        lightDownLed(led);
        _delay_ms(timeOff);
        timeOff += duration / 1000;
        timeOn -= duration / 1000;
    }
    lightUpLed(led);
}
/**
 * @brief fade out a led
 *
 * @param led
 * @param duration
 */
void fadeOutLed(int led, int duration)
{
    enableOneLed(led);
    double time = duration / 1000;
    for (int i = 0; i < duration; i++)
    {
        lightUpLed(led);
        _delay_ms(1.0 - time);
        lightDownLed(led);
        _delay_ms(time);
        time += 0.01;
    }
    lightDownLed(led);
}
/**
 * @brief light up leds 1-4
 *
 */
void lightUpInOrder()
{
    for (int i = 0; i < 4; i++)
    {
        enableOneLed(i);
        lightUpLed(i);
        _delay_ms(2000);
    }
}
void ledCountdown()
{
    lightUpAllLeds();
    _delay_ms(1000);
    for (int i = 3; i >= 0; i--)
    {
        lightDownLed(i);
        _delay_ms(1000);
    }
}
/**
 * @brief flash leds /amount/ times
 *
 * @param led
 * @param amount
 */

void flashLed(int led, int amount)
{
    enableOneLed(led);
    for (int i = 0; i < amount; i++)
    {
        lightUpLed(led);
        _delay_ms(1000);
        lightDownLed(led);
        _delay_ms(1000);
    }
}
/**
 * @brief chaos panic and destruction
 *
 */
void CHAOS()
{
    srand(0);
    enableAllLeds();
    while (1)
    {
        int currLed = rand() % 4;
        int time = (rand() % 900) + 100;
        lightUpLed(currLed);
        _delay_ms(time);
        lightDownLed(currLed);
    }
}
/**
 * @brief walk through an array and light up led nr
 *
 * @param array
 */
void walkThroughSequence(int array[10])
{
    // int sequence[10];
    // srand(0)
    // for(int i = 0; i < 10;i++){
    //     sequence[i]=rand()%4;
    // }

    for (int i = 0; i < 10; i++)
    {
        enableOneLed(array[i] - 1);
        lightUpLed(array[i] - 1);
        _delay_ms(1000);
        lightDownLed(array[i] - 1);
        _delay_ms(1000);
    }
}
/**
 * @brief light up leds based on string
 *
 * @param string
 */
void stringLightUp(char string[])
{
    // stringLightUp("abcAcba");
    for (int i = 0; i < strlen(string); i++)
    {
        switch (string[i])
        {
        case 'a':
            enableOneLed(0);
            lightUpLed(0);
            break;
        case 'b':
            enableOneLed(1);
            lightUpLed(1);
            break;
        case 'c':
            enableOneLed(2);
            lightUpLed(2);
            break;
        case 'd':
            enableOneLed(3);
            lightUpLed(3);
            break;
        default:
            lightDownAllLeds();
        }
        _delay_ms(1000);
    }
}
void ledsDancing(int duration)
{
    for (int i = 0; i < 4; i++)
    {
        enableOneLed(i);
    }
    for (int i = 0; i < duration; i++)
    {
        for (int i = 0; i < 4; i++)
        {
            lightUpLed(i);
            _delay_ms(100);
        }
        for (int i = 0; i < 4; i++)
        {
            lightDownLed(i);
            _delay_ms(100);
        }
    }
}
void ledsDancingReverse(int duration)
{
    for (int i = 0; i < 4; i++)
    {
        enableOneLed(i);
    }
    for (int i = 0; i < duration; i++)
    {
        for (int i = 4; 0 <= i; i--)
        {
            lightUpLed(i);
            _delay_ms(100);
        }
        for (int i = 4; 0 <= i; i--)
        {
            lightDownLed(i);
            _delay_ms(100);
        }
    }
}
void dot()
{
    lightUpAllLeds();
    _delay_ms(1000);
    lightDownAllLeds();
    _delay_ms(1000);
}
void dash()
{
    lightUpAllLeds();
    _delay_ms(3000);
    lightDownAllLeds();
    _delay_ms(1000);
}

/**
 * @brief convert your string to morse! wow!
 *
 * @param string the sentence you want to convert!!!
 */
void toMorse(char string[])
{

    // a dot lasts for one second
    // a dash last for three seconds
    // the space between dots and dashes that are part of the same letter is one second
    // the space between different letters is three seconds
    // the space between different words is seven seconds
    initUSART();
    enableAllLeds();
    lightUpAllLeds();
    for (int i = 3; 0 <= i; i--)
    {
        _delay_ms(1000);
        lightDownLed(i);
    }
    _delay_ms(1000);
    for (int i = 0; i < strlen(string); i++)
    {
        switch (toupper(string[i]))
        {
        case 'A':
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'B':
            dash();
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'C':
            dash();
            dot();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'D':
            dash();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'E':
            dot();
            _delay_ms(2000);
            break;
        case 'F':
            dot();
            dot();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'G':
            dash();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'H':
            dot();
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'I':
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'J':
            dot();
            dash();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case 'K':
            dash();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'L':
            dot();
            dash();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'M':
            dash();
            dash();
            _delay_ms(2000);
            break;
        case 'N':
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'O':
            dash();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case 'P':
            dot();
            dash();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'Q':
            dash();
            dash();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'R':
            dot();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case 'S':
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case 'T':
            dash();
            _delay_ms(2000);
            break;
        case 'U':
            dot();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'V':
            dot();
            dot();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'W':
            dot();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case 'X':
            dash();
            dot();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case 'Y':
            dash();
            dot();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case 'Z':
            dash();
            dash();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case '0':
            dash();
            dash();
            dash();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case '1':
            dot();
            dash();
            dash();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case '2':
            dot();
            dot();
            dash();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case '3':
            dot();
            dot();
            dot();
            dash();
            dash();
            _delay_ms(2000);
            break;
        case '4':
            dot();
            dot();
            dot();
            dot();
            dash();
            _delay_ms(2000);
            break;
        case '5':
            dot();
            dot();
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case '6':
            dash();
            dot();
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case '7':
            dash();
            dash();
            dot();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case '8':
            dash();
            dash();
            dash();
            dot();
            dot();
            _delay_ms(2000);
            break;
        case '9':
            dash();
            dash();
            dash();
            dash();
            dot();
            _delay_ms(2000);
            break;
        case ' ':
            _delay_ms(4000);
            break;
        default:
            for (int i = 0; i < 15; i++)
            {
                lightUpAllLeds();
                _delay_ms(500);
                lightDownAllLeds();
            }
            break;
        }
        printf("SIGN %d: %c\n", i + 1, string[i]);
    }
    printf("%s", string);
    for (int i = 0; i < 10; i++)
    {
        lightUpAllLeds();
        _delay_ms(100);
        lightDownAllLeds();
        _delay_ms(100);
    }
    ledsDancing(5);
    ledsDancingReverse(5);
}

int isOn(int led)
{
    if (bit_is_set(PORTB, led))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void playPuzzle(uint8_t sequence[], int index)
{
    for (int i = 0; i < index; i++)
    {
        _delay_ms(DELAY);
        lightToggleOneLed(sequence[i] + 1);
        _delay_ms(DELAY);
        lightToggleOneLed(sequence[i] + 1);
    }
}