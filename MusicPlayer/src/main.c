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
#include <leds.h>

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
int scrolling_text=0;
// This ISR runs every time TCNT0 equals the value in the OCRA register
ISR(TIMER2_COMPA_vect)
{
  if ((counter % MULTIPLE) == 0)
  {
    if(!songPaused()){
    timer++;
    printTimer(timer_ptr);
    }
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
    }
    }
  else{
    if(buttonPushed(2)){
      pauseSong();
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
    while(current_screen==START_SCREEN){
      writeLine("MUSIC PLAYER BY FIFI");
      
    }
    while(current_screen==MUSIC_SELECT_SCREEN){
      getSong(selected_song);
      
    }
    while(current_screen==MUSIC_PLAY_SCREEN){
      int song_playing=playSong(selected_song,timer_ptr);
      if(song_playing==2){
        selected_song=selected_song+1<MAX_SONGS ? selected_song+1 : 0;
        _delay_ms(1000);
      }
      else if(song_playing==1){
        selected_song=selected_song-1>=0 ? selected_song-1 : 2;
         _delay_ms(1000);
      }
      else if(buttonPushed(2)){
        current_screen=MUSIC_SELECT_SCREEN;
        break;
      }
      scrolling_text=1;
      getSong(selected_song);
      scrolling_text=0;
      timer=0;
    }
    
  }
    return 0;
}