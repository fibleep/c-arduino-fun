
#include <leds.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

int main()
{
    toMorse("i hate c so much");
    return 0;
}
