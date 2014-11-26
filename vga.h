#ifndef VGA_H
#define VGA_H

#define VGA_GWIDTH  320
#define VGA_GHEIGHT 200
#define VGA_TWIDTH  80
#define VGA_THEIGHT 25

static int vga_graphics()
{
#asm
    mov   ah,#$00;
    mov   al,#$13;
    int   #$10
#endasm
}

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

static int vga_text()
{
#asm
    mov   ah,#$00;
    mov   al,#$03;
    int   #$10
#endasm
}

static void vga_putc(int x, int y, int c)
{
#asm
  mov   bx,sp
  mov   ax,[bx+4]  ! y
  imul  ax,#80
  mov   cx,[bx+2]  ! x
  add   cx,ax      ! y*80+x
  imul  cx,#2
  mov   dx,[bx+6]  ! c

  push  ds
  mov   bx,#$B800  ! VGA text segment
  mov   ds,bx
  mov   bx,cx
  mov   [bx],dx
  pop   ds
#endasm
}

#endif
