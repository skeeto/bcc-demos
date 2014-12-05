#ifndef PORT_H
#define PORT_H

#include "int.h"

static inline int16_t inportb(int16_t port)
{
    volatile uint8_t value;
    asm volatile ("in   %%dx, %%ax\n"
                  : "=a"(value)
                  : "d"(port)
                  : /* no clobber */);
    return value;
}

static inline void outportb(int16_t port, uint8_t value)
{
    asm volatile ("out   %%al, %%dx\n"
                  : /* no output */
                  : "d"(port), "a"(value)
                  : /* no clobber */);
}

#endif
