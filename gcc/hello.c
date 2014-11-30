__asm__(".code16gcc\n"
        "call  main\n"
        "mov   $0x4C,%ah\n"
        "int   $0x21\n");

#include "int.h"
#include "time.h"
#include "vga.h"

int main(void)
{
    vga_on();
    vga_clear(4);
    vga_line((struct point){1, 1}, (struct point){318, 198}, 7);
    vga_line((struct point){317, 198}, (struct point){0, 1}, 8);
    vga_line((struct point){1, 198}, (struct point){318, 1}, 7);
    vga_line((struct point){317, 1}, (struct point){0, 198}, 8);
    vga_rect((struct rect){{120, 60}, {200, 140}}, 14);
    msleep(1500);
    for (int i = 0; i < 256; i++) {
        vga_clear(i);
        vga_vsync();
        msleep(100);
    }
    vga_off();
    return 1;
}
