#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <buttons.h>

void initADC()
{
  ADMUX |= (1 << REFS0);
  ADMUX |= (1 << MUX0);                                 // Set up of reference voltage. We choose 5V as reference.
  ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // Determine a sample rate by setting a division factor. Used division factor: 128
  ADCSRA |= (1 << ADEN);                                // Enable the ADC
}

int main()
{
  initUSART();
  enableAllButtons();
  initADC();
  initDisplay();
  while (1)
  {
    ADCSRA |= (1 << ADSC);                 // Start the analog --> digital conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wait until the conversion is completed
    uint16_t value = ADC;
    // Read the result
    writeNumber(value);
    printf("Value: %d\n", value);
  }
  return 0;
}