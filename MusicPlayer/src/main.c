#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <potentiometer.h>
#include <buttons.h>
#include <avr/interrupt.h>
#include <buzzer.h>
#include <music_player.h>
#include <timer.h>

#define START_SCREEN 0
#define MUSIC_SELECT_SCREEN 1
#define MUSIC_PLAY_SCREEN 2
#define MAX_SONGS 3
#define MULTIPLE 250

uint8_t current_screen = START_SCREEN;
uint8_t selected_song = 0;
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

ISR(PCINT1_vect)
{
  if(current_screen==START_SCREEN){
    if(anyButtonPushed()){
      current_screen=MUSIC_SELECT_SCREEN;
    }
  }
  else if(current_screen==MUSIC_SELECT_SCREEN){
    if(current_screen==MUSIC_PLAY_SCREEN && buttonPressed(2)){
        current_screen=MUSIC_SELECT_SCREEN;
    }
    if(buttonPushed(3)){
      selected_song=(selected_song+1<MAX_SONGS) ? selected_song+1 : 0;
    }
    else if(buttonPushed(1)){
      selected_song=(selected_song>0) ? selected_song-1 : MAX_SONGS-1;
    }
    else if(buttonPushed(2)){
      current_screen=MUSIC_PLAY_SCREEN;
      timer=0;
      startTimer();
    }
    }
  else{
    if(buttonPressed(2)){
        current_screen=MUSIC_SELECT_SCREEN;
    }
  }
  }

int main()
{
  initUSART();
  initDisplay();
  initADC();
  enableAllButtons();
  enableBuzzer();
  playTone(100000,1); 
  initializeSongList();
  sei();
  while(1){
    printf("swtiching screens...\n");
    while(current_screen==START_SCREEN){
      printf("start screen...\n");
      writeLine("MUSIC PLAYER BY FIFI");
    }
    while(current_screen==MUSIC_SELECT_SCREEN){
      printf("select screen...%d\n",selected_song);
      getSong(selected_song);
      
    }
    while(current_screen==MUSIC_PLAY_SCREEN){
    //  playSong(selected_song);
      writeTimer(timer_ptr);

    }
    
  }
    return 0;
}