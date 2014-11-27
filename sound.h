/**
 * https://courses.engr.illinois.edu/ece390/books/labmanual/io-devices-speaker.html
 * http://www.fysnet.net/snd.htm
 */
#ifndef SOUND_H
#define SOUND_H

static void __tone(unsigned period)
{
#asm
  push  bp
  mov   bp,sp
  mov   al,#182
  out   $43,al
  mov   ax,[bp+4]
  out   $42,al
  mov   al,ah
  out   $42,al
  in    al,$61
  or    al,#3
  out   $61,al
  pop   bp
#endasm
}

static void tone(int freq)
{
    __tone(1193180L / freq);
}


static void quiet(void)
{
#asm
  in    al,$61
  and   al,$FC
  out   $61,al
#endasm
}

#endif
