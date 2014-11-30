struct joystick {
    int16_t x, y;
    bool a, b;
};

void joystick_read(struct joystick *a, struct joystick *b)
{
    asm("mov  $0x84, %%ah\n"
        "mov  $1, %%dx\n"
        "int  $0x15\n"
        : "=ax"(a->x), "=bx"(a->y), "=cx"(b->x), "=dx"(b->y)
        : /**/
        : /**/);
    uint16_t buttons = 0;
    asm("mov  $0x84, %%ah\n"
        "mov  $0, %%dx\n"
        "int  $0x15\n"
        : "=ax"(buttons)
        : /**/
        : "%bx", "%cx", "%dx", "%flags");
    a->a = !(buttons & (1 << 4));
    a->b = !(buttons & (1 << 5));
    b->a = !(buttons & (1 << 6));
    b->b = !(buttons & (1 << 7));
}
