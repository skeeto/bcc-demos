#include "math.h"

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

static void vga_pixel(volatile struct point p, uint8_t color)
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
    asm("mov   %%al, %%ah\n"
        "mov   $0, %%di\n"
        "push  %%ax\n"
        "shl   $16, %%eax\n"
        "pop   %%ax\n"
        "mov   $16000, %%cx\n"
        "rep\n"
        "stosl\n"
        : /* no outputs */
        : "al"(color)
        : "%cx");
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
