#include <conio.h>
#include "vga.h"

int main(void)
{
    long i;
    vga_graphics();
    while (!kbhit())
        vga_set(rand()%320, rand()%200, rand()%16);
    getch();
    vga_text();
    vga_cursor(40, 12);
    while (!kbhit())
        vga_putc(rand()%80, rand()%25, 'a' + (rand()%26), rand() % 16);
    getch();
    vga_text(); // clear
    return 0;
}
