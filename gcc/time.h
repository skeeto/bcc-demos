static uint32_t get_tick()
{
    volatile unsigned long result;
    asm("push  %%es\n"
        "mov   $0,%%bx\n"
        "mov   %%bx,%%es\n"
        "mov   $0x046C,%%bx\n"
        "mov   %%es:(%%bx),%%eax\n"
        "pop   %%es\n"
        : "=a"(result)
        : /* no inputs */
        : "%bx");
    return result;
}

static void msleep(uint32_t ms)
{
    uint32_t us = ms * 1000;
    asm("mov   $0x86, %%ah\n"
        "int   $0x15\n"
        : /* no outputs */
        : "cx"(us >> 16), "dx"(us & 0x16)
        : "%ah", "%flags");
}
