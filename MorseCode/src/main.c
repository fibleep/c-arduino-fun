
#include <leds.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    initUSART();
    toMorse("i hate c so much");
    return 0;
}
