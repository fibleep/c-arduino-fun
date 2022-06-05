#include <buzzer.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <buttons.h>

#define B0  31
#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62
#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976
#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951
#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978

#define WHOLE 64
#define HALF 32
#define QUARTER 16
#define EIGHTH 8
#define SIXTEENTH 4

#define CURRENT_SONG_AMOUNT 3

typedef struct{
    int frequency;
    uint32_t duration;
}NOTE;

typedef struct{
char name[40];
NOTE notes[40];
int size;
}SONG;

typedef struct{
uint8_t index;
SONG song;
} SONG_LIST;

SONG_LIST song_list[CURRENT_SONG_AMOUNT];

int pause = 0;

void initializeSongList(){
    for(uint8_t i=0;i<CURRENT_SONG_AMOUNT;i++){
        addSong(i);
        song_list[i].index=i+1;
    }
}

void addSong(int index){
    SONG to_return;
    if(index==0){
        strcpy(to_return.name,"The Imperial March");
        int notes[] = {A4,A4,A4,F4,C4,A4,F4,C4,A4,E5,E5,E5,F5,C4,A4,F4,C4,A4,A5,A4,A4};
        uint8_t duration[] = {QUARTER,QUARTER,QUARTER,EIGHTH,EIGHTH,QUARTER,EIGHTH,EIGHTH,WHOLE,QUARTER,QUARTER,QUARTER,EIGHTH,EIGHTH,QUARTER,EIGHTH,EIGHTH,WHOLE,QUARTER,EIGHTH,EIGHTH};
        // int notes[] = {};
        // uint8_t duration[] = {};
       // printf("DEBUG FOR SONGS NOTES: %d DURATIONS: %d\n",(sizeof(notes)/sizeof(notes[0])),(sizeof(duration)/sizeof(duration[0])));
        
        for(int i=0;i<sizeof(notes)/sizeof(notes[0]);i++){
            NOTE note;
            to_return.size=sizeof(notes)/sizeof(notes[0]);
            note.frequency=notes[i];
            note.duration=1000/(64/duration[i]);
            to_return.notes[i]=note;
        }
    }
    if(index==1){
        strcpy(to_return.name,"Ode to Joy");
        int notes[] = {E4,F4,G4,G4,F4,E4,D4,C4,C4,D4,E4,E4,D4,D4};
        uint8_t duration[]={HALF,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,QUARTER,HALF};
        // int notes[] = {};
        // uint8_t duration[] = {};
        
        for(int i=0;i<sizeof(notes)/sizeof(notes[0]);i++){
            NOTE note;
            note.frequency=notes[i];
            to_return.size=sizeof(notes)/sizeof(notes[0]);
            note.duration=1000/(64/duration[i]);
            to_return.notes[i]=note;
        }
    }
     if(index==2){
        strcpy(to_return.name,"London Bridge");
        int notes[] = {G3,A3,G3,F3,E3,F3,G3,D3,E3,F3,E3,F3,G3,D3,G3,E3,C3,G3,A3,G3,F3,E3,F3,G3,D3,E3,F3,E3,F3,G3,D3,G3,E3,C3};
        uint8_t duration[] = {HALF,HALF,WHOLE,QUARTER,QUARTER,HALF,WHOLE,HALF,HALF,WHOLE,HALF,HALF,WHOLE,HALF,HALF,WHOLE,QUARTER,QUARTER,HALF,WHOLE,WHOLE,QUARTER,QUARTER,WHOLE,HALF,HALF,WHOLE,QUARTER,QUARTER,HALF,WHOLE,HALF,HALF,WHOLE};
        // int notes[] = {};
        // uint8_t duration[] = {};
        for(int i=0;i<sizeof(notes)/sizeof(notes[0]);i++){
            NOTE note;
            to_return.size=sizeof(notes)/sizeof(notes[0]);
            note.frequency=notes[i];
            note.duration=1000/(64/duration[i]);
            to_return.notes[i]=note;
        }
    }
    song_list[index].song=to_return;
}
int playSong(int index,int* timer){
    printf("\n================\n");
    printf("NOW PLAYING: \n");
    printf(song_list[index].song.name);
    printf("\n================\n");
    startTimer();
    pause=0;
    for(int i=0;i<song_list[index].song.size;i++){
         if(buttonPressed(2)){
            pause=1;
            return 0;
        }
        if(buttonPushed(1)){
            pause=1;
            return 1;
        }
        if(buttonPushed(3)){
            pause=1;
            return 2;
        }


        if(pause==0){
        playTone(song_list[index].song.notes[i].frequency,song_list[index].song.notes[i].duration);
        }
        else{
            i--;
        }
    }
    pause=1;
    return 1;
}
void getSong(int index){
    writeLine(song_list[index].song.name);
}

void pauseSong(){
    pause=!pause;
}
int songPaused(){
    return pause;
}
