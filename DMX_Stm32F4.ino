
/* Example.
Fade in channel 1 on all outputs.
*/

#include "DMX_Stm32f4_lib.h"

long Timer = 0;
byte dim = 0;

void setup() {

  OUT1 = 1; // OTPUT1 PIN (PC11)
  OUT2 = 2; // OTPUT1 PIN (PC2)
  OUT3 = 3; // OTPUT1 PIN (PC3)
  OUT4 = 4; // OTPUT1 PIN (PC4)
  OUT5 = 5; // OTPUT1 PIN (PC5)
  OUT6 = 6; // OTPUT1 PIN (PC6)
  OUT7 = 7; // OTPUT1 PIN (PC7)
  OUT8 = 8; // OTPUT1 PIN (PC8)

  pinMode(PC_1, OUTPUT);
  pinMode(PC_2, OUTPUT);
  pinMode(PC_3, OUTPUT);
  pinMode(PC_4, OUTPUT);
  pinMode(PC_5, OUTPUT);
  pinMode(PC_6, OUTPUT);
  pinMode(PC_7, OUTPUT);
  pinMode(PC_8, OUTPUT);

  DMX_begin();
}

void loop() {

  if (millis() > Timer)
  {
    Timer = millis() + 200;

    for (byte i = 0; i < 8; i++)
    {
      buffer_dmx[i][1] = dim;  ////  OUT1-8, CHANNEL 1 /// SYNTAX:  buffer_dmx[OUT(0-7)][CHANNEL(1-512)]
    }

    dim++;
  }

  DMX_writebuffer();

}
