#ifndef TIME_H
#define TIME_H

static int time()
{
#asm
  mov   ah,#$00
  int   $1A
  mov   ax,dx
#endasm
}

#endif
