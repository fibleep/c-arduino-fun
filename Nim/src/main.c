#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <potentiometer.h>
#include <buttons.h>
#include <avr/interrupt.h>

#define START_NUMBER 21
#define MAX_NUMBER 3
int seed;

char player[] = "CP";
int main()
{
  initUSART();
  initDisplay();
  initADC();
  enableAllButtons();
  while (1)
  {
    if (anyButtonPushed())
    {
      seed = getValue();
      break;
    }
  }
  int toTake = MAX_NUMBER;
  int turnCount = 0;
  int currTurn = 3;
  int matches = START_NUMBER;
  int *taken, *stack;
  taken = (int *)malloc(21 * sizeof(int));
  stack = (int *)malloc(21 * sizeof(int));

  srand(seed);
  currTurn = seed % 2;
  writeNumberAndWait(seed, 2500);
  while (1)
  {
    writeNumberToSegment(0, toTake);
    writeCharToSegment(1, *(player + currTurn));
    writeNumberToSegment(2, matches / 10);
    writeNumberToSegment(3, matches % 10);

    if (buttonPushed(1) && toTake - 1 > 0)
    {
      toTake--;
      _delay_ms(500);
    }
    else if (buttonPushed(2))
    {
      *(taken + turnCount) = toTake;
      *(stack + turnCount) = matches;
      turnCount++;
      currTurn = !currTurn;
      matches -= toTake;
      if (matches - 1 == 0)
      {
        if (turnCount % 2 == 1)
        {
          currTurn = !currTurn;
        }
        for (int i = 0; i < turnCount; i++)
        {
          printf("%c took %d matches from stack of %d\n", player[currTurn], taken[i], stack[i]);

          currTurn = !currTurn;
        }
        printf("%c lost the game! sucks to suck!\n", player[currTurn]);
        while (1)
        {
          writeCharToSegment(0, player[currTurn]);
          writeCharToSegment(1, 'B');
          writeCharToSegment(2, 'A');
          writeCharToSegment(3, 'D');
        }
      }
      _delay_ms(250);
      while (1)
      {
        if (!buttonPushed(2))
        {
          writeCharToSegment(1, *(player + currTurn));
          _delay_ms(100);
          writeCharToSegment(1, ' ');
          _delay_ms(100);
        }
        else
        {
          break;
        }
      }
      if (currTurn)
      {
        toTake = MAX_NUMBER;
      }
      else
      {
        if ((matches - 1) % (MAX_NUMBER + 1) == 0)
        {

          toTake = rand() % (MAX_NUMBER - 1) + 1;
        }
        else
        {
          toTake = (matches - 1) % (MAX_NUMBER + 1);
        }
      }
      _delay_ms(500);
    }
    else if (buttonPushed(3) && toTake + 1 < 4)
    {
      printf("2");
      toTake++;
      _delay_ms(500);
    }
  }
  free(taken);
  free(stack);
  return 0;
}