/*
  Only for stm32f4xx !!!
  Lib for transmit DMX512 packet to 8 outputs (easily may be expands to 16)  using DMA and timer TIM1. Simple and powerfull.
  Almost dont use CPU!
  Eats about 20KB of RAM
  FRAMERATE - 41 Packets/sec.
  Write in by Andy Roc https://github.com/Andyroc / https://www.instagram.com/andy.roc/ / https://vk.com/andy.rock
  15 jan. 2021
*/


uint16_t dma_buffer[6000];
uint8_t buffer_dmx[8][513];
uint32_t timerTick = 0;
uint8_t dma_bitcount;
uint16_t dma_bytecount;

byte OUT1 = -1;
byte OUT2 = -1;
byte OUT3 = -1;
byte OUT4 = -1;
byte OUT5 = -1;
byte OUT6 = -1;
byte OUT7 = -1;
byte OUT8 = -1;

#define OUTPORT GPIOС // output port GPIOA, GPIOB, GPOC ....

void DMX_begin()
{
    RCC->AHB1ENR |= 1 << 22; 
    RCC->APB2ENR |= 1; 
    TIM1->DIER = (1 << 8); 
    TIM1->PSC = 336; 
    TIM1->ARR = 1; 
    TIM1->CR1 = 1; 
    DMA2_Stream5->CR = (6 << 25) | (1 << 11) | (1 << 10) | (1 << 8) | (1 << 6); // Ch:6,WORD,MINC,CIRC,Mem2per
    DMA2_Stream5->M0AR = (uint32_t)dma_buffer;
    DMA2_Stream5->PAR = (uint32_t) & (OUTPORT->ODR); 
    DMA2_Stream5->NDTR = 6000; DMA2_Stream5->CR |= 1; 

    OUTPORT->ODR |= (1 << OUT1);
    OUTPORT->ODR |= (1 << OUT2);
    OUTPORT->ODR |= (1 << OUT3);
    OUTPORT->ODR |= (1 << OUT4);
    OUTPORT->ODR |= (1 << OUT5);
    OUTPORT->ODR |= (1 << OUT6);
    OUTPORT->ODR |= (1 << OUT7);
    OUTPORT->ODR |= (1 << OUT8);
}

void DMX_writebuffer()
{


    if (millis() > timerTick)  //// 
    {
        timerTick = millis() + 24;

        for (byte i = 0; i < 30; i++) /// BREAK
        {
            dma_buffer[i] = 0x0;
        }
        for (byte i = 30; i < 33; i++) /// MAB
        {
            dma_buffer[i] = 0xffff;
        }
        for (byte i = 0; i < 4; i++) /// ZERO FRAME
        {
            buffer_dmx[i][0] = 0;
        }
        dma_bytecount = 0;
        dma_bitcount = 0;
        for (int i = 33; i < 6000; i++) /// 512 FRAMES
        {
            if (i < 5676)
            {
                if (dma_bytecount == 0)
                {
                    dma_buffer[i] = 0x0;
                    dma_bytecount = 1;
                }
                else if (dma_bytecount > 0 && dma_bytecount < 9)
                {
                    dma_buffer[i] = (bitRead(buffer_dmx[0][dma_bitcount], dma_bytecount - 1) << OUT1) | (bitRead(buffer_dmx[1][dma_bitcount], dma_bytecount - 1) << OUT2) | (bitRead(buffer_dmx[2][dma_bitcount], dma_bytecount - 1) << OUT3) | (bitRead(buffer_dmx[3][dma_bitcount], dma_bytecount - 1) << OUT4) | (bitRead(buffer_dmx[4][dma_bitcount], dma_bytecount - 1) << OUT5) | (bitRead(buffer_dmx[5][dma_bitcount], dma_bytecount - 1) << OUT6) | (bitRead(buffer_dmx[6][dma_bitcount], dma_bytecount - 1) << OUT7) | (bitRead(buffer_dmx[7][dma_bitcount], dma_bytecount - 1) << OUT8); /// bytes
                    dma_bytecount++;
                    if (dma_bytecount == 9)
                    {
                        dma_bitcount++;
                    }
                }
                else if (dma_bytecount == 9)
                {
                    dma_buffer[i] = 0xffff;
                    dma_bytecount++;
                }
                else if (dma_bytecount == 10)
                {
                    dma_buffer[i] = 0xffff;
                    dma_bytecount = 0;
                }
            }
            else /// PAUSE BETWEEN PACKETS
            {
                dma_buffer[i] = 0xffff;
            }
        }
    }
}
