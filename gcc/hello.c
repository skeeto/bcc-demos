__asm__(".code16gcc\n"
        "call  main\n"
        "mov   $0x4C,%ah\n"
        "int   $0x21\n");

static void print(char *string)
{
    asm("mov   $0x09, %%ah\n"
        "int   $0x21\n"
        : /* no output */
        : "dx"(string)
        : "%ah");
}

static void printl(unsigned long n)
{
    /* volatile */ char buffer[12];
    int i = sizeof(buffer);
    buffer[--i] = '$';
    if (n == 0)
        buffer[--i] = '0';
    else
        for (; n > 0; n /= 10)
            buffer[--i] = '0' + (n % 10);
    print(buffer + i);
}

int main(void)
{
    print("Hello, world!\n$");
    printl(123456789);
    return 1;
}
