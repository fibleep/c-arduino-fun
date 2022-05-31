#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <potentiometer.h>
#include <buttons.h>
#include <avr/interrupt.h>


int main()
{
  initUSART();
  initDisplay();
  initADC();
  enableAllButtons();

  
  while(1){
  writeLine("sussy baka 1 2 345");
  }
  return 0;
}