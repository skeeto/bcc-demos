/*
 * http://dc0d32.blogspot.com/2010/06/real-mode-in-c-with-gcc-writing.html
 */
__asm__(".code16gcc\n");

static void print(char *string)
{
    asm("mov   $0x09, %%ah\n"
        "int   $0x21\n"
        : /* no output */
        : "dx"(string)
        : "%ah");
}

static void printc(char c)
{
    asm("mov   $0x02, %%ah\n"
        "int   $0x21\n"
        : /* no output */
        : "dx"(c)
        : "%ah");
}

int main(void)
{
    printc('H');
    printc('i');
    printc('\n');
    print("Hello, world!\n$");
    return 1;
}
