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

static void msleep(int ms)
{
    uint32_t count = ms / 54; // 18.2 Hz
    uint32_t last = get_tick();
    while (count) {
        uint32_t now = get_tick();
        if (now != last) {
            last = now;
            count--;
        }
    }
}
