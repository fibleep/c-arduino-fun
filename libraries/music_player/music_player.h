#include <buzzer.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>

typedef struct{
    int frequency;
    uint32_t duration;
}NOTE;

typedef struct{
    char name[40];
    NOTE notes[50];
}SONG;

typedef struct{
    uint8_t index;
    SONG song;
} SONG_LIST;


void initializeSongList();
SONG addSong(int index);
int playSong(int index,int* timer);
void getSong(int index);
void pauseSong();
int songPaused();