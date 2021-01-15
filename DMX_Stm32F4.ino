
/* Example.
Fade in channel 1 on all outputs.
*/

#include "DMX_Stm32f4_lib.h"

long Timer = 0;
byte dim = 0;

void setup() {

  OUT1 = 1; // OTPUT1 PIN (PС1)
  OUT2 = 2; // OTPUT1 PIN (PС2)
  OUT3 = 3; // OTPUT1 PIN (PС3)
  OUT4 = 4; // OTPUT1 PIN (PС4)
  OUT5 = 5; // OTPUT1 PIN (PС5)
  OUT6 = 6; // OTPUT1 PIN (PС6)
  OUT7 = 7; // OTPUT1 PIN (PС7)
  OUT8 = 8; // OTPUT1 PIN (PС8)

  pinMode(PС_1, OUTPUT);
  pinMode(PС_2, OUTPUT);
  pinMode(PС_3, OUTPUT);
  pinMode(PС_4, OUTPUT);
  pinMode(PС_5, OUTPUT);
  pinMode(PС_6, OUTPUT);
  pinMode(PС_7, OUTPUT);
  pinMode(PС_8, OUTPUT);

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
