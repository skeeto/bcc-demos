/**
 * https://courses.engr.illinois.edu/ece390/books/labmanual/io-devices-speaker.html
 */
#ifndef SOUND_H
#define SOUND_H

static void tone(int freq)
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

static void quiet(void)
{
#asm
  in    al,$61
  and   al,$FC
  out   $61,al
#endasm
}

#endif
