#include "keyboard.h"
#include "hw_io.h"

const char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char getchar(void)
{
    while (1)
    {
        if (inb(0x64) & 1)
        {
            uint8_t scancode = inb(0x60);
            if (scancode < sizeof(scancode_ascii))
            {
                char c = scancode_ascii[scancode];
                if (c != 0)
                    return c;
            }
        }
    }
}
