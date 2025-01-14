#include <stdlib.h>      // for rand()

#include "keyboard.h"
#include "draw.h"

byte *logo =
 // 1234567890123456789012345678901234567890
   "TTTTTTT EEEEE XXXXXXX RRRRR   I   SSSS  "
   "   T    E        X    R    R  I  S    S "
   "   T    E        X    R    R  I  S      "
   "   T    EEEE     X    RRRRR   I   SSSS  "
   "   T    E        X    R  R    I       S "
   "   T    E        X    R   R   I  S    S "
   "   T    EEEEE    X    R    R  I   SSSS  ";

void drawLogo() {
   byte *s = logo;
   for(byte r=0;r<7;r++) {
      for(byte c=0;c<40;c++) {
         byte tile = 0;
         switch(*s++) {
            case 'T': tile = 1; break;
            case 'E': tile = 1; break;
            case 'X': tile = 1; break;
            case 'R': tile = 1; break;
            case 'I': tile = 1; break;
            case 'S': tile = 1; break;
         }
         if(tile) {
            byte ch  = piece_chars[tile];
            byte col = piece_colors[tile];
            draw_tile(c+12,r+1,ch,col);
         }
      }
   }
}

// introduction screen
void introScreen() {
   cls();

   drawLogo();

   #ifdef TRS80
   draw_string(21, 9,"for the TRS-80 Model I", REVERSE_OFF);
   #endif

   #ifdef SOL20
   draw_string(16, 9,"for the SOL-20 Terminal Computer", REVERSE_OFF);
   #endif

   #ifdef GP
   draw_string(14, 9,"for the General Processor Model T/08", REVERSE_OFF);
   #endif

   #ifdef POLY88
   draw_string(20, 9,"for the POLY-88 Computer", REVERSE_OFF);
   #endif

   draw_string(16,11,"  by Antonino Porcino, dec 2021", REVERSE_OFF);

#ifdef POLY88
   print_string(14,13,
      "    Keys: "
      ESC_REVERSE_ON"<I>"ESC_REVERSE_OFF" "
      ESC_REVERSE_ON"<J>"ESC_REVERSE_OFF" "
      ESC_REVERSE_ON"<K>"ESC_REVERSE_OFF" "
      ESC_REVERSE_ON"<L>"ESC_REVERSE_OFF" "
      ESC_REVERSE_ON"<SPACE>"ESC_REVERSE_OFF"     "
   , REVERSE_OFF);
   print_string(21,15,"press "ESC_REVERSE_ON"<RETURN>"ESC_REVERSE_OFF" to start", REVERSE_OFF);
#else
   print_string(14,13,
      "    Keys: "
      ESC_REVERSE_ON" I "ESC_REVERSE_OFF" "
      ESC_REVERSE_ON" J "ESC_REVERSE_OFF" "
      ESC_REVERSE_ON" K "ESC_REVERSE_OFF" "
      ESC_REVERSE_ON" L "ESC_REVERSE_OFF" "
      ESC_REVERSE_ON" SPACE "ESC_REVERSE_OFF"     "
   , REVERSE_OFF);
   print_string(21,15,"press "ESC_REVERSE_ON" RETURN "ESC_REVERSE_OFF" to start", REVERSE_OFF);
#endif

   // wait for key released
   while(test_key(SCANCODE_RETN));

   // wait for key press and do the coloured animation   
   while(!test_key(SCANCODE_RETN)) {
      // TODO music      
      rand();  // extract random numbers, making rand() more "random"
   }
}

