
/* Example.
Fade in channel 1 on all outputs.
*/

#include "DMX_Stm32f4_lib.h"

long Timer = 0;
byte dim = 0;

void setup() {

  OUT1 = 1; // OTPUT1 PIN (PC1)
  pinMode(PC_1, OUTPUT);  //OTPUT1 PIN MODE
  OUT2 = 2; // OTPUT2 PIN (PC2)
  pinMode(PC_2, OUTPUT);  //OTPUT2 PIN MODE
  OUT3 = 3; // OTPUT3 PIN (PC3)
  pinMode(PC_3, OUTPUT);  //OTPUT3 PIN MODE
  OUT4 = 4; // OTPUT4 PIN (PC4)
  pinMode(PC_4, OUTPUT);  //OTPUT4 PIN MODE
  OUT5 = 5; // OTPUT5 PIN (PC5)
  pinMode(PC_5, OUTPUT);  //OTPUT5 PIN MODE
  OUT6 = 6; // OTPUT6 PIN (PC6)
  pinMode(PC_6, OUTPUT);  //OTPUT6 PIN MODE
  OUT7 = 7; // OTPUT7 PIN (PC7)
  pinMode(PC_7, OUTPUT);  //OTPUT7 PIN MODE
  OUT8 = 8; // OTPUT8 PIN (PC8)
  pinMode(PC_8, OUTPUT);  //OTPUT8 PIN MODE

  DMX_begin();
}

void loop() {

  if (millis() > Timer)
  {
    Timer = millis() + 200;

    for (byte i = 0; i < 8; i++)
    {
      buffer_dmx[i][1] = dim;  ////  SYNTAX: buffer_dmx[OUT(0-7)][CHANNEL(1-512)]
    }

    dim++;
  }

  DMX_writebuffer();

}
