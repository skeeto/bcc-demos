#ifndef VGA_H
#define VGA_H

static void vga_set(int x, int y, int color)
{
#asm
  mov   bx,sp
  mov   ax,[bx+4]  ! y
  imul  ax,#320
  mov   cx,[bx+2]  ! x
  add   cx,ax      ! y*320+x
  mov   dx,[bx+6]  ! color

  push  ds
  mov   bx,#$A000  ! VGA segment
  mov   ds,bx
  mov   bx,cx
  mov   [bx],dl
  pop   ds
#endasm
}

static int vga_enable()
{
#asm
    mov   ah,#$00;
    mov   al,#$13;
    int   #$10
#endasm
}

static int vga_disable()
{
#asm
    mov   ah,#$00;
    mov   al,#$03;
    int   #$10
#endasm
}

#endif
