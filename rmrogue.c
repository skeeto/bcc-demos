#include <conio.h>
#include "vga.h"
#include "time.h"

/*
 * 59 - 68 (F1-F9)
 * 71 72 73
 * 75    77
 * 79 80 81
 * 82 83
 */

int main(void)
{
    int x = 0, y = 0;
    vga_text();
    for (;;) {
        int value;
        char key, code;
        vga_putc(x, y, '@', YELLOW);
        value = getch();
        key = value & 0xff;
        code = value >> 8;
        vga_putc(x, y, ' ', 0);
        if (key == 0) {
            switch (code) {
                case 72:
                    y--;
                    break;
                case 77:
                    x++;
                    break;
                case 80:
                    y++;
                    break;
                case 75:
                    x--;
                    break;
            }
        } else {
            switch (key) {
            case 'h':
                x--;
                break;
            case 'j':
                y++;
                break;
            case 'k':
                y--;
                break;
            case 'l':
                x++;
                break;
            }
        }
    }
    return 0;
}
