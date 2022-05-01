
#include <leds.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 35
    initUSART();
    char base[] = {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };
    char result[10];
    srand(0);
    for (int i = 0; i < 10; i++)
    {
        result[i] = base[rand() % 35];
    }
    toMorse(result);
    //  toMorse("i hate c so much");
    return 0;
}
