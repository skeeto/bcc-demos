#include "math.h"

struct joystick {
    uint16_t x, y;
    bool a, b;
};

static struct {
    uint16_t min, max;
} joystick_limits[2] = {{0xffff, 0x0000}, {0xffff, 0x0000}};

static void joystick_read2(struct joystick *a, struct joystick *b)
{
    asm volatile ("mov  $0x84, %%ah\n"
                  "mov  $1, %%dx\n"
                  "int  $0x15\n"
                  : "=a"(a->x), "=b"(a->y), "=c"(b->x), "=d"(b->y)
                  : /**/
                  : /**/);
    joystick_limits[0].min = min(joystick_limits[0].min, a->x);
    joystick_limits[0].max = max(joystick_limits[0].max, a->x);
    joystick_limits[0].min = min(joystick_limits[0].min, a->y);
    joystick_limits[0].max = max(joystick_limits[0].max, a->y);
    joystick_limits[1].min = min(joystick_limits[1].min, b->x);
    joystick_limits[1].max = max(joystick_limits[1].max, b->x);
    joystick_limits[1].min = min(joystick_limits[1].min, b->y);
    joystick_limits[1].max = max(joystick_limits[1].max, b->y);
    uint16_t buttons = 0;
    asm volatile ("mov  $0x84, %%ah\n"
                  "mov  $0, %%dx\n"
                  "int  $0x15\n"
                  : "=a"(buttons)
                  : /**/
                  : "bx", "cx", "dx", "flags");
    a->a = !(buttons & (1 << 4));
    a->b = !(buttons & (1 << 5));
    b->a = !(buttons & (1 << 6));
    b->b = !(buttons & (1 << 7));
}

static void joystick_read(struct joystick *joystick)
{
    struct joystick dummy;
    joystick_read2(joystick, &dummy);
}
