#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>

int main()
{
  initUSART();
  initDisplay();
  while (1)
  {
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10000; j++)
      {
        writeNumberToSegment(0, i);
        writeNumberToSegment(1, (i + 1) % 10);
        writeNumberToSegment(2, (i + 2) % 10);
        writeNumberToSegment(3, (i + 3) % 10);
      }
    }
  }
  return 0;
}