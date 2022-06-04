#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <timer.h>
#include <display.h>

#define MULTIPLE 250

uint32_t counter = 0;
int timer = 0;
int* timer_ptr = &timer;

// This ISR runs every time TCNT0 equals the value in the OCRA register
ISR(TIMER2_COMPA_vect)
{
  if ((counter % MULTIPLE) == 0)
  {
    timer++;
  }
  counter++;
}

// This ISR runs every time TCNT0 equals the TOP value (255)
// ISR(TIMER2_OVF_vect)
// {
//   counter++;
//   PORTB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5);
// }

int main()
{
  initUSART();
  initDisplay();
  startTimer();                                      // initialize Timer 0
  DDRB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5); // Place the LEDs in output mode

  while (1)
  {
    // printf("Meanwhile we are at a total of %d interrupts.\n\n", counter);

    writeTimer(timer_ptr);
    
  }

  return 0;
}