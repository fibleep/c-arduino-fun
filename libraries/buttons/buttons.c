#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <leds.h>
#define true 1
#define false 0
#define superfalse 2
void isB0Pressed()
{
    initUSART();
    DDRC &= ~_BV(PC1); /* Set up DDR, instead of using ( 1 << PC1 ) we use the

                        * macro _BV( bit ). (BV stands for "Bit Value") */
#ifdef DEBUG           // The following code is only printed when DEBUG is defined
    printf("DDRC: ");
    printBinaryByte(DDRC);
#endif

    PORTC |= _BV(PC1); /* Activate pull-up of C1.
                        * We use the macro _BV( bit ) instead of ( 1 << PC 1 ) */
#ifdef DEBUG
    printf("\nPORTC: ");
    printBinaryByte(PORTC);
#endif

    while (1)
    {
        printf("\nPINC: ");
        printBinaryByte(PINC);
        if (bit_is_clear(PINC, PC1)) /* instead of (!(PINC & ( 1 << PC1 ))) we use the macro bit_is_clear */
        {
            printf(" - Button 1 pressed!\n");
        }
        else
        {
#ifdef DEBUG
            printf(" - Button 1 NOT pressed!!\n");
#endif
        }
        _delay_ms(1000);
    }
}
void enableButton(int button)
{
    DDRC &= ~_BV(button);
    PORTC |= _BV(button);
    PCMSK1 |= _BV(button);
    PCICR |= _BV(PCIE1);
}
void enableAllButtons()
{
    DDRC &= ~_BV(PC1);
    PORTC |= _BV(PC1);
    PCMSK1 |= _BV(PC1);
    DDRC &= ~_BV(PC2);
    PORTC |= _BV(PC2);
    PCMSK1 |= _BV(PC2);
    DDRC &= ~_BV(PC3);
    PORTC |= _BV(PC3);
    PCMSK1 |= _BV(PC3);
    PCICR |= _BV(PCIE1);
}
int buttonPushed(int button)
{
    if (bit_is_clear(PINC, button))
    {
        _delay_us(1000);
        if (bit_is_clear(PINC, button))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int buttonPressed(int button){
    if(buttonPushed(button)){
        _delay_ms(500);
        if(buttonPushed(button)){
            return 1;
        }
    }
    return 0;
}
int buttonClicked(button){
    if(buttonPushed(button)){
        if(buttonReleased(button)){
            return 1;
        }
    }
    return 0;
}
int anyButtonPushed()
{
    return buttonPushed(1) || buttonPushed(2) || buttonPushed(3);
}

int buttonReleased(int button)
{
    return !buttonPushed(button);
}
void generatePuzzle(uint8_t *sequence[], int size)
{
    for (int i = 0; i < size; i++)
    {
        *(sequence + i) = rand() % 3;
    }
}
void printPuzzle(uint8_t sequence[], int size)
{
    printf("[ ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf(" ]");
}
int readInput(int toPress, int pressed)
{
    if ((toPress + 1) == pressed)
    {
        printf("%d is correct! ", pressed);
        for (int i = 0; i < 6; i++)
        {
            lightToggleOneLed(0);
            _delay_ms(100);
        }
        return true;
    }
    else if (pressed == 0)
    {
        _delay_us(10);
        return false;
    }
    else
    {
        _delay_us(10);
        return superfalse; // <---- SUPER FALSE
    }
}