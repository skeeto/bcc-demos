#include "vga.h"

int main(void)
{
    long i;
    vga_enable();
    for (i = 0; i < 1000000; i++)
        vga_set(rand()%320, rand()%200, rand()%16);
    vga_disable();
    return 0;
}
