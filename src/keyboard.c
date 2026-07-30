#include "keyboard.h"
#include "vga.h"
#include "hw_io.h"

static volatile char last_char = 0;

static const char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
     0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',   0, ' '
};

static const char scancode_ascii_uppercase[] = {

};

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);

    
    if (!(scancode & 0x80)) {
        if (scancode < sizeof(scancode_ascii)) {
            last_char = scancode_ascii[scancode];
        }
    }

    outb(0x20, 0x20);
}

char getchar(void) {
    while (last_char == 0) {
        __asm__ volatile ("hlt");
    }
    char c = last_char;
    last_char = 0; // cls char
    return c;
}
