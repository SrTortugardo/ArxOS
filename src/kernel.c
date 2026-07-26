#include "shell.h"
#include "vga.h"

void kernel_main(void)
{
    clear_screen();
    shell_run();

    while (1)
    {
        __asm__ volatile("hlt");
    }
}
