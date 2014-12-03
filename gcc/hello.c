asm (".code16gcc\n"
     "call  main\n"
     "mov   $0x4C,%ah\n"
     "int   $0x21\n");

#include "int.h"
#include "time.h"
#include "vga.h"
#include "joystick.h"

int main(void)
{
    vga_on();
    vga_clear(4);
    vga_line((struct point){1, 1}, (struct point){318, 198}, 7);
    vga_line((struct point){317, 198}, (struct point){0, 1}, 8);
    vga_line((struct point){1, 198}, (struct point){318, 1}, 7);
    vga_line((struct point){317, 1}, (struct point){0, 198}, 8);
    vga_rect((struct rect){{120, 60}, {200, 140}}, 14);
    msleep(1000);

    struct joystick joy;
    joystick_read(&joy);
    if (joy.x != 0 || joy.y != 0) {
        while (!joy.a) {
            joystick_read(&joy);
            vga_vsync();
            int min = joystick_limits[0].min, max = joystick_limits[0].max;
            vga_clear(32 + ((joy.y - min) * 16) / max);
        }
    } else {
        for (int i = 0; i < 256; i++) {
            vga_clear(i);
            vga_vsync();
            msleep(100);
        }
    }
    vga_off();
    return 1;
}
