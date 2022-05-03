#include <util/delay.h>
#include <avr/io.h>
#include <buttons.h>

void initADC()
{
    ADMUX |= (1 << REFS0);                                // Set up of reference voltage. We choose 5V as reference.
    ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Determine a sample rate by setting a division factor. Used division factor: 128
    ADCSRA |= (1 << ADEN);
}
void enableButtonInput(int button)
{
    switch (button)
    {
    case 0:
        ADMUX |= (1 << MUX0);
        enableButton(PC1);
        break;
    case 1:
        ADMUX |= (1 << MUX1);
        enableButton(PC2);
        break;
    case 2:
        ADMUX |= (1 << MUX2);
        enableButton(PC3);
        break;
    }
}
void enableAllButtonInput()
{
    for (int i = 0; i < 3; i++)
    {
        enableButtonInput(i);
    }
}
int getValue()
{
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    uint16_t value = ADC;
    return value;
}