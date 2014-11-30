__asm__(".code16gcc\n"
        "call  main\n"
        "mov   $0x4C,%ah\n"
        "int   $0x21\n");

#include "int.h"
#include "time.h"

#define VGA_PWIDTH  320
#define VGA_PHEIGHT 200

struct point {
    short x, y;
};

struct rect {
    struct point tl, br;
};

/* Switch to VGA mode 13 and set ES. */
static void vga_on()
{
    asm("mov   $0x0013, %%ax\n"
        "int   $0x10\n"
        "mov   $0xA000, %%ax\n"
        "mov   %%ax, %%es\n"
        : /* no outputs */
        : /* no inputs */
        : "%ax");
}

static void vga_off()
{
    asm("mov   $0x0003, %%ax\n"
        "int   $0x10\n"
        "mov   $0xA000, %%dx\n"
        "mov   %%dx, %%es\n"
        : /* no outputs */
        : /* no inputs */
        : "%ax", "%dx");
}

static inline void vga_pixel(volatile struct point p, uint8_t color)
{
    asm("imul  $320, %%bx\n"
        "add   %%ax, %%bx\n"
        "mov   %%cl, %%es:(%%bx)\n"
        : /* no outputs */
        : "ax"(p.x), "bx"(p.y), "cl"(color)
        : "%dx");
}

static void vga_clear(char color)
{
    volatile struct point p;
    for (p.y = 0; p.y < VGA_PHEIGHT; p.y++)
        for (p.x = 0; p.x < VGA_PWIDTH; p.x++)
            vga_pixel(p, color);
}

static inline int abs(int x)
{
    return x < 0 ? -x : x;
}

static void vga_line(struct point a, struct point b, uint8_t color)
{
    int dx = abs(b.x - a.x), sx = a.x < b.x ? 1 : -1;
    int dy = abs(b.y - a.y), sy = a.y < b.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    for(;;) {
        vga_pixel(a, color);
        if (a.x == b.x && a.y == b.y)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            a.x += sx;
        }
        if (e2 < dy) {
            err += dx;
            a.y += sy;
        }
    }
}

static void vga_rect(struct rect r, uint8_t color)
{
    vga_line(r.tl, (struct point){r.br.x, r.tl.y}, color);
    vga_line(r.tl, (struct point){r.tl.x, r.br.y}, color);
    vga_line(r.br, (struct point){r.br.x, r.tl.y}, color);
    vga_line(r.br, (struct point){r.tl.x, r.br.y}, color);
}

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
    vga_off();
    return 1;
}
