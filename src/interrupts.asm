[bits 32]
global idt_load
global irq0_stub
global irq1_stub

extern timer_handler
extern keyboard_handler

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

; IRQ0 timer stub
irq0_stub:
    pusha
    call timer_handler
    popa
    iretd

; IRQ1 keyboard stub
irq1_stub:
    pusha
    call keyboard_handler
    popa
    iretd
    