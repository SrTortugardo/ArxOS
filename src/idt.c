#include "idt.h"
#include "hw_io.h"


struct idt_entry idt[256];
struct idt_ptr   idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel       = sel;
    idt[num].always0   = 0;
    idt[num].flags     = flags;
}

static void pic_remap(void) {
    // Remap Master PIC to 0x20-0x27 and Slave PIC to 0x28-0x2F
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20); // Master vector offset
    outb(0xA1, 0x28); // Slave vector offset
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Unmask IRQ0 (timer) and IRQ1 (keyboard)
    outb(0x21, 0xFC); 
    outb(0xA1, 0xFF);
}

void idt_init(void) {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base  = (uint32_t)&idt;

    // Clear table
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // 1. Remap PIC
    pic_remap();

    // 2. Set IDT entries (0x08 is your code segment)
    idt_set_gate(32, (uint32_t)irq0_stub, 0x08, 0x8E); // IRQ0 -> Vector 32
    idt_set_gate(33, (uint32_t)irq1_stub, 0x08, 0x8E); // IRQ1 -> Vector 33

    // 3. Load IDTR and enable hardware interrupts
    idt_load((uint32_t)&idtp);
    __asm__ volatile ("sti");
}