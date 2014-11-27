#include <conio.h>
#include "vga.h"

struct border {
    int dx, x;
    int dy, y;
    int tick;
};

void border_step(struct border *b)
{
    if (b->tick++ >= 100) {
        b->x += b->dx;
        b->y += b->dy;
        b->tick = 0;
        if (b->x == VGA_TWIDTH) {
            b->x = VGA_TWIDTH - 1;
            b->dy = 1;
            b->dx = 0;
        } else if (b->y == VGA_THEIGHT) {
            b->y = VGA_THEIGHT - 1;
            b->dx = -1;
            b->dy = 0;
        } else if (b->x < 0) {
            b->x = 0;
            b->dx = 0;
            b->dy = -1;
        } else if (b->y < 0) {
            b->y = 0;
            b->dx = 1;
            b->dy = 0;
        }
        vga_cursor(b->x, b->y);
    }
    vga_putc(b->x, b->y, 0xB0, GREEN << 4 | YELLOW);
}

int main(void)
{
    long i;
    struct border border;
    memset(&border, 0, sizeof(border));
    border.dx = 1;

    vga_graphics();
    while (!kbhit())
        vga_set(rand()%320, rand()%200, rand()%16);
    getch();

    vga_text();
    while (!kbhit()) {
        border_step(&border);
        vga_putc(rand()%80, rand()%25, 'a' + (rand()%26), rand() % 16);
    }
    getch();

    vga_text(); // clear
    return 0;
}
