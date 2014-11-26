#include <stdio.h>
#include <conio.h>
#include "vga.h"

int front;
unsigned char life[2][VGA_GWIDTH / 8][VGA_GHEIGHT];

int get(int x, int y)
{
    if (x < 0)
        x =  VGA_GWIDTH;
    else if (x >= VGA_GWIDTH)
        x -= VGA_GWIDTH;
    if (y < 0)
        y += VGA_GHEIGHT;
    else if (y >= VGA_GHEIGHT)
        y -= VGA_GHEIGHT;
    return !!(life[front][x / 8][y] & (1 << (x % 8)));
}

void set(int x, int y, int alive)
{
    int bit = 1 << (x % 8);
    if (alive)
        life[!front][x / 8][y] |= bit;
    else
        life[!front][x / 8][y] &= ~bit;
}

void draw()
{
    int x, y;
    for (y = 0; y < VGA_GHEIGHT; y++) {
        for (x = 0; x < VGA_GWIDTH; x++) {
            int alive = get(x, y);
            vga_set(x, y, alive ? LIGHT_GRAY : BLACK);
        }
    }
}

void init()
{
    long i;
    for (i = 0; i < sizeof(life); i++)
        ((char *)life)[i] = rand();
}

void step()
{
    int x, y;
    for (y = 0; y < VGA_GHEIGHT; y++) {
        for (x = 0; x < VGA_GWIDTH; x++) {
            int sum = 0;
            sum += get(x +  1, y +  1);
            sum += get(x +  0, y +  1);
            sum += get(x + -1, y +  1);
            sum += get(x +  1, y +  0);
            sum += get(x + -1, y +  0);
            sum += get(x +  1, y + -1);
            sum += get(x +  0, y + -1);
            sum += get(x + -1, y + -1);
            if (sum == 3)
                set(x, y, 1);
            else if (sum == 2)
                set(x, y, get(x, y));
            else
                set(x, y, 0);
        }
    }
    front = !front;
}

int main(void)
{
    printf("Initializing...\n");
    init();
    vga_graphics();
    while (!kbhit()) {
        draw();
        step();
    }
    vga_text();
    return 0;
}
