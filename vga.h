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
  push  bp
  mov   bp,sp
  push  ds
  mov   bx,[bp+6]  ! y
  imul  bx,#320
  add   bx,[bp+4]  ! bx = y * 320 + x
  mov   ax,#$A000  ! VGA segment
  mov   ds,ax
  mov   ax,[bp+8]  ! color
  mov   [bx],al
  pop   ds
  pop   bp
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
  push  bp
  mov   bp,sp
  push  ds
  mov   bx,[bp+6]  ! y
  imul  bx,#80
  add   bx,[bp+4]  ! bx = y * 80 + x
  imul  bx,#2
  mov   dl,[bp+8]  ! c
  mov   dh,[bp+10] ! color
  mov   ax,#$B800  ! VGA text segment
  mov   ds,ax
  mov   [bx],dx
  pop   ds
  pop   bp
#endasm
}

static void vga_cursor(int x, int y)
{
#asm
  push  bp
  mov	bp,sp
  mov	dh,[bp+6]
  mov	dl,[bp+4]
  mov	ax,#$0200
  mov	bx,#7
  int	$10
  pop   bp
#endasm
}

#endif
