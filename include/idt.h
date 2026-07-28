#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// 1. Structure for an IDT entry (Gate Descriptor)
struct idt_entry {
    uint16_t base_low;   // Lower 16 bits of handler function memory address
    uint16_t sel;        // Kernel code segment selector in GDT (usually 0x08)
    uint8_t  always0;    // Always set to 0
    uint8_t  flags;      // Flags: Present, Privilege level, Type (0x8E for 32-bit IDT gate)
    uint16_t base_high;  // Upper 16 bits of handler function memory address
} __attribute__((packed));

// 2. Structure for the IDT Pointer register (IDTR argument)
struct idt_ptr {
    uint16_t limit;      // Table size - 1
    uint32_t base;       // Table memory address
} __attribute__((packed));

// 3. Function prototypes
void idt_init(void);
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

// 4. Declarations for Assembly handlers and stubs in interrupts.asm
extern void idt_load(uint32_t ptr);
extern void irq0_stub(void);
extern void irq1_stub(void);

#endif