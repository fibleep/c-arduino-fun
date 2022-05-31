#include <avr/interrupt.h>
#include <avr/io.h>


#define MULTIPLE 250

void startTimer()
{
  // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
  // We choose FAST PWM; TCNT0 counts to 255
  TCCR2A |= _BV(WGM20) | _BV(WGM21); // CTC?

  // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
  // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
  TCCR2B |= _BV(CS22) | _BV(CS21); // CS02 = 1 and CS00 = 1 --> prescaler factor is now 1024 (= every 64 us)

  // STEP 3: enable INTERRUPTS
  // Enable interrupts for 2 cases: TCNT0 == TOP and TCNT0 == OCR0A
  // TIMSK2 |= _BV(OCR2A);  // enable OCRA interrupt
  TIMSK2 |= _BV(OCIE2A); // enable OCRA interrupt

  sei(); // enable interrupts globally
}
