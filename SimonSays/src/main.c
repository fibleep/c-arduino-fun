
#include <leds.h>
#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <buttons.h>
#include <avr/interrupt.h>
#include <stdlib.h>

int button_pushed = 0;
ISR(PCINT1_vect)
{
	if (buttonPushed(PC1) == 1)
	{
		lightToggleOneLed(1);
		_delay_ms(500);
		lightToggleOneLed(1);
		button_pushed = 1;
	}
	else if (buttonPushed(PC2) == 1)
	{
		lightToggleOneLed(2);
		_delay_ms(500);
		lightToggleOneLed(2);
		button_pushed = 2;
	}
	else if (buttonPushed(PC3) == 1)
	{
		lightToggleOneLed(3);
		_delay_ms(500);
		lightToggleOneLed(3);
		button_pushed = 3;
	}
}

int main()
{
	enableAllButtons();
	initUSART();
	int counter = 0;
	enableAllLeds();
	sei();
	while (button_pushed == 0)
	{
		lightToggleOneLed(0);
		_delay_ms(100);
		counter += 1;
	}
	lightDownAllLeds();
	button_pushed = 0;
	uint8_t sequence[10];
	srand(counter);
	generatePuzzle(sequence, 10);
	// printPuzzle(sequence,10);
	cli();
	_delay_ms(1000);
	ledCountdown();
	for (int i = 1; i < 11; i++)
	{
		cli();
		playPuzzle(sequence, i);
		_delay_ms(500);
		button_pushed = 0;
		int correct = 1;
		sei();
		for (int j = 0; j < i; j++)
		{
			int next = 0;
			button_pushed = 0;
			while (next == 0)
			{
				next = readInput(sequence[j], button_pushed);
			}
			if (next == 2)
			{
				printf("you sussy baka ");
				correct = 0;
				break;
			}
		}
		if (correct == 0)
		{
			printf("sequence broken! \n");
			i--;
			correct = 1;
		}
		else
		{
			printf("next sequence! \n");
		}
	}
	return 0;
}
