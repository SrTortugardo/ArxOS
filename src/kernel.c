// src/kernel.c
#include "shell.h"
#include "vga.h"
#include "idt.h"
#include "hw_io.h"

volatile uint32_t timer_ticks = 0;

// IRQ0 Handler (Timer)
void timer_handler(void) {
    timer_ticks++;
    
    // Send EOI signal to PIC
    outb(0x20, 0x20);
}

void kernel_main(void)
{
    // 1. Initialize Interrupts (Remaps PIC, loads IDT, runs 'sti')
    idt_init();

    // 2. Clear screen and start shell
    clear_screen();
    shell_run();

    // 3. Idle loop: CPU sits in low-power state waiting for IRQs
    while (1)
    {
        __asm__ volatile("hlt");
    }
}