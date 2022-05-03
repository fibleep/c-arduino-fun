#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <buttons.h>
#include <potentiometer.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// char *log;
// char log = malloc(100 * sizeof(int));
// int indx = 0;
// void writeLinesOnHeap(char sentence[])
// {

//   log[indx] = malloc(strlen(sentence) + 1);
//   strcpy(log[indx], sentence);
//   indx++;
// }
int main()
{
  // char log = malloc(100 * sizeof(int));
  initUSART();
  initDisplay();
  initADC();
  enableButtonInput(0);
  while (1)
  {
    ADCSRA |= (1 << ADSC);                 // Start the analog --> digital conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wait until the conversion is completed
    uint16_t value = ADC;
    printf("%d\n", value);
    writeNumber(value);
    if (value < 1000)
    {
      break;
    }
  }
  for (int i = 0; i < 100; i++)
  {
    printf("%d: I am not allowed to speak in class.\n", i + 1);
  }
  writeLinesOnHeap("I am not allowed to speak in class.");
  return 0;
}