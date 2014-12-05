asm (".code16gcc\n"
     "call  main\n"
     "mov   $0x4C,%ah\n"
     "int   $0x21\n");

#include "int.h"
#include "time.h"
#include "vga.h"
#include "joystick.h"
#include "tone.h"

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
        joystick_calibrate();
        tone_on();
        while (!joy.a) {
            joystick_read(&joy);
            vga_vsync();
            int xmin = joystick_config[0].xmin;
            int xmax = joystick_config[0].xmax;
            int ymin = joystick_config[0].ymin;
            int ymax = joystick_config[0].ymax;
            vga_clear(32 + ((joy.y - ymin) * 16) / ymax);
            tone(131 + ((joy.x - xmin) * 392) / xmax);
        }
        tone_off();
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
