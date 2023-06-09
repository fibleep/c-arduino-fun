#include <display.h>
#include <buttons.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define SPACE 0xFF

int timer_initialized=0;


/* Segment byte maps for numbers 0 to 9 */
const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};

/* Byte maps to select digit 1 to 4 */
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};
/**
 * @brief alphabet map
 *
 */
const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                0xC1, 0xD5, 0x89, 0x91, 0xA4};

void initDisplay()
{
  sbi(DDRD, LATCH_DIO);
  sbi(DDRD, CLK_DIO);
  sbi(DDRB, DATA_DIO);
}

// loop through seven segments of LED display and shift the correct bits in the
// data register
void shift(uint8_t val, uint8_t bitorder)
{
  uint8_t bit;

  for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++)
  {
    if (bitorder == LSBFIRST)
    {
      bit = !!(val & (1 << i));
    }
    else
    {
      bit = !!(val & (1 << (7 - i)));
    }
    // write bit to register
    if (bit == HIGH)
      sbi(PORTB, DATA_DIO);
    else
      cbi(PORTB, DATA_DIO);

    // Trigger the clock pin so the display updates
    sbi(PORTD, CLK_DIO);
    cbi(PORTD, CLK_DIO);
  }
}

// Writes a digit to a certain segment-> Segment 0 is the leftmost->
void writeNumberToSegment(uint8_t segment, uint8_t value)
{
  cbi(PORTD, LATCH_DIO);
  shift(SEGMENT_MAP[value], MSBFIRST);
  shift(SEGMENT_SELECT[segment], MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

// Writes a nuber between 0 and 9999 to the display-> To be used in a loop->
void writeNumber(int number)
{
  if (number < 0 || number > 9999)
    return;
  writeNumberToSegment(0, number / 1000);
  writeNumberToSegment(1, (number / 100) % 10);
  writeNumberToSegment(2, (number / 10) % 10);
  writeNumberToSegment(3, number % 10);
}

void addDecimal(int segment){
  cbi(PORTD, LATCH_DIO);
  shift(0b01111111, MSBFIRST);
  shift(0xF2, MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}


void writeTimer(int* number)
{
  if (number < 0 || number > 9999)
  return;
  TIMER *timer_ptr,timer;
  timer_ptr=&timer;
  addTimer(timer_ptr,number);

  writeNumberToSegment(0, timer.minutes_tens);
  writeNumberToSegment(1,timer.minutes);
  addDecimal(1);
  writeNumberToSegment(2, timer.seconds_tens);
  writeNumberToSegment(3, timer.seconds);
}

void addTimer(TIMER* timer,int* number){
  if(!timer_initialized){
    timer->minutes=(uint8_t*)malloc(sizeof(uint8_t));
    timer->minutes_tens=(uint8_t*)malloc(sizeof(uint8_t));
    timer->seconds=(uint8_t*)malloc(sizeof(uint8_t));
    timer->seconds_tens=(uint8_t*)malloc(sizeof(uint8_t));
    timer->minutes=0;
    timer->minutes_tens=0;

    timer_initialized=1;
  }

  if(*number==60){
    if(timer->minutes==9){
      timer->minutes_tens++;
      timer->minutes=0;
    }else{
      (timer->minutes)++;
    }
    *number=0;
  }else{
    timer->seconds_tens=(*number / 10) % 10;
    timer->seconds=*number%10;
  }
}

void printTimer(int* number){
  if (number < 0 || number > 9999)
  return;
  TIMER *timer_ptr,timer;
  timer_ptr=&timer;
  addTimer(timer_ptr,number);
  printf("%d%d : %d%d\n",timer.minutes_tens,timer.minutes,timer.seconds_tens,timer.seconds);
}


// Writes a number between 0 and 9999 to the display and makes sure that it stays there a certain number of millisecs->
// Note: the timing is approximate; the amount of time writeNumberToSegment takes is not accounted for->
void writeNumberAndWait(int number, int delay)
{
  if (number < 0 || number > 9999)
    return;
  for (int i = 0; i < delay / 20; i++)
  {
    writeNumberToSegment(0, number / 1000);
    _delay_ms(5);
    writeNumberToSegment(1, (number / 100) % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (number / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, number % 10);
    _delay_ms(5);
  }
}

void writeCharToSegment(uint8_t segment, char character)
{
  character = toupper(character);
  if (!isalpha(character))
  {
    cbi(PORTD, LATCH_DIO);
    shift(SPACE, MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
  else
  {
    cbi(PORTD, LATCH_DIO);
    shift(ALPHABET_MAP[character - 65], MSBFIRST);
    shift(SEGMENT_SELECT[segment], MSBFIRST);
    sbi(PORTD, LATCH_DIO);
  }
}

void writeString(char str[])
{
  for (int i = 0; i < 4; i++)
  {
    writeCharToSegment(i, str[i]);
  }
}

void writeStringAndWait(char str[], int delay)
{
  for (int i = 0; i < delay; i++)
  {
    writeString(str);
  }
}

void resetDisplay(){
  for(int i=0;i<4;i++){
    writeCharToSegment(i,SPACE);
  }
}

void writeLine(char line[]){
  int bound = strlen(line);
  int current_bound=0;
  int scroll_speed = 1000;

  for(int i=0;i<bound;i++){
    for(int ii=0;ii<scroll_speed;ii++){
      int segment=0;
        for(int j=current_bound;j<current_bound+4;j++){
          
          if(anyButtonPushed()){
              i=ii=j=1000;
              break;
            }
          
          if(j>bound){
            writeCharToSegment(segment,SPACE);
          }
          else if((line[j]>='0' && line[j]<='9')){
            writeNumberToSegment(segment,line[j]-'0');
          }
          else{
            writeCharToSegment(segment,line[j]);
          }
          segment++;
        }
        resetDisplay();
    }
    current_bound=current_bound+1;
    }
}