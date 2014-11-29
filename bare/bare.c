/* Initialization code (replaces bcc's crt0). */
#asm
  mov   dx,cs
  add   dx,#__segoff
  mov   ds,dx
  call  _main
  mov   ah,#$4C
  int   #$21
#endasm

static void print(char *string)
{
#asm
  push  bp
  mov   bp,sp
  mov   dx,[bp+4]
  mov   ah,#$09
  int   #$21
  pop   bp
#endasm
}

int main(void)
{
    char *message = "Hello, World!\n$";
    print(message);
    return 1;
}
