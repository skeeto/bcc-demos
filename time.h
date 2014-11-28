#ifndef TIME_H
#define TIME_H

static long time()
{
#asm
  push  ds
  pushf
  cli
  !! begin critical section
    mov   ax,#$0000
    mov   ds,ax
    mov   bx,#$046C
    mov   ax,[bx+0]
    mov   dx,[bx+2]
  !! end critical section
  popf
  pop   ds
#endasm
}

/* Beware midnight cross-over bug. */
static void wait(int ms)
{
    long end = time() + ms / 51; // 18.2 Hz
    while (time() < end);
}

#endif
