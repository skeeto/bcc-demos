#ifndef VGA_H
#define VGA_H

#define VGA_GWIDTH  320
#define VGA_GHEIGHT 200
#define VGA_TWIDTH  80
#define VGA_THEIGHT 25

enum VGA_COLOR {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GRAY, DARK_GRAY,
    LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA,
    YELLOW, WHITE
};

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

static void vga_putc(int x, int y, int c, int color)
{
#asm
  mov   bx,sp
  mov   ax,[bx+4]  ! y
  imul  ax,#80
  mov   cx,[bx+2]  ! x
  add   cx,ax      ! y*80+x
  imul  cx,#2
  mov   dl,[bx+6]  ! c
  mov   dh,[bx+8]  ! color

  push  ds
  mov   bx,#$B800  ! VGA text segment
  mov   ds,bx
  mov   bx,cx
  mov   [bx],dx
  pop   ds
#endasm
}

static void vga_cursor(int x, int y)
{
#asm
  mov	bx,sp
  mov	ax,[bx+4]
  mov	dh,al
  mov	ax,[bx+2]
  mov	dl,al
  mov	ah,#$02
  mov	bx,#7
  int	$10
#endasm
}

#endif
