#include "types.h"
#include "keyboard.h"

#define SCREEN_WIDTH   64
#define SCREEN_HEIGHT  16
#define SCREEN_ADDRESS 0xF800

#define REVERSE_OFF 0
#define REVERSE_ON  0

#define FRAME_VERT      0xAD
#define FRAME_HORIZL    0x87
#define FRAME_HORIZR    0xB8
#define FRAME_NW_CORNER 0xAC
#define FRAME_NE_CORNER 0xA5
#define FRAME_SW_CORNER 0xA9
#define FRAME_SE_CORNER 0x8D

#define FRAME_BOARD_VERTL 0xB8
#define FRAME_BOARD_VERTR 0x87

#define CH_BACKGROUND '.'
#define CH_SPACE      ' '

#define CRUNCH_CHAR_1   0x95
#define CRUNCH_COLOR_1  REVERSE_OFF

#define CRUNCH_CHAR_2   0xAA
#define CRUNCH_COLOR_2  REVERSE_OFF

#define FILLED_GR_CHAR  128
#define FILLED_GR_COLOR REVERSE_OFF

byte test_key(byte key);
byte read_keyboard();
byte player_input();
byte read_poly88_keyboard();
byte read_poly88_keyboard_status();

#define SCANCODE_RETN 0x0d

// test a specific key
byte test_key(byte key) {
   if(read_poly88_keyboard_status()==0) return 0;
   return read_poly88_keyboard() == key ? 1 : 0;
}

// reads the poly88 keyboard status
byte _key_status = 0;
INLINE byte read_poly88_keyboard_status() {   
   __asm
   push h
   lxi h,0xc0c
   mov a,m
   pop h
   or a
   jnz nope
   mvi a,1
   jmp bye
nope:
   xor a
bye:
   ld (__key_status),a      
   __endasm;
   return _key_status;
}

// reads the POLY88 keyboard
byte _key = 0;
INLINE byte read_poly88_keyboard() {
   __asm
   push h
   lxi h,0xc0c
   dcr m
   inx h
   mov a,m
   pop h
   ld (__key),a   
   __endasm;
   return _key;
}

byte player_input() {
   
   if(read_poly88_keyboard_status()==0) return 0;

   byte key = read_poly88_keyboard(); 

        if(key=='I' || key=='i') return KEY_ROTATE;
   else if(key=='J' || key=='j') return KEY_LEFT;
   else if(key=='K' || key=='k') return KEY_DOWN;
   else if(key=='L' || key=='l') return KEY_RIGHT;
   else if(key==' ') return KEY_DROP;
   else if(key==13) return 13;  // TODO handle differently
   else return 0;
}

