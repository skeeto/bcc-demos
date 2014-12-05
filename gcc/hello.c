asm (".code16gcc\n"
     "call  main\n"
     "mov   $0x4C,%ah\n"
     "int   $0x21\n");

#include "int.h"
#include "time.h"
#include "vga.h"
#include "joystick.h"
#include "tone.h"
#include "mouse.h"

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
        do {
            joystick_read(&joy);
            vga_vsync();
            int xmin = joystick_config[0].xmin;
            int xmax = joystick_config[0].xmax;
            int ymin = joystick_config[0].ymin;
            int ymax = joystick_config[0].ymax;
            vga_clear(32 + ((joy.y - ymin) * 16) / ymax);
            tone(131 + ((joy.x - xmin) * 392) / xmax);
        } while (!joy.a);
        tone_off();
    } else {
        mouse_init();
        struct mouse mouse;
        do {
            mouse = mouse_read();
            vga_clear(32 + (mouse.y * 16) / (MOUSE_YMAX + 1));
            vga_vsync();
        } while (!mouse.left);
    }
    vga_off();
    return 1;
}
