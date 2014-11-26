#include "vga.h"

int main(void)
{
    long i;
    vga_graphics();
    for (i = 0; i < 10000; i++)
        vga_set(rand()%320, rand()%200, rand()%16);
    vga_text();
    vga_cursor(40, 12);
    for (i = 0; i < 10000; i++)
        vga_putc(rand()%80, rand()%25, 'a' + (rand()%26), rand() % 16);
    for(i=0;i<100000;i++);
    return 0;
}
