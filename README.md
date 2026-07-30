# ArxOS

A 32-bit hobby operating system kernel written from scratch. ArxOS boots via Multiboot bootloader and provides a simple interactive shell environment running in protected mode on x86 hardware.

**Status:** Early development. Currently boots and runs a basic shell. Not UEFI compatible.

---

## Features

- **32-bit x86 Protected Mode** — Runs directly on compatible hardware or emulation
- **Multiboot Compatible** — Boots via Multiboot-compliant bootloaders (GRUB)
- **Interactive Shell** — Command-line interface with basic built-in commands
- **VGA Text Mode Output** — Direct memory writes to VGA buffer for display
- **Keyboard Input** — PS/2 keyboard support for user input
- **Hardware I/O Abstraction** — Port I/O utilities for hardware communication

---

## Architecture

```
.
├── boot.asm           Bootloader entry point, Multiboot header
├── linker.ld          Linker script for memory layout (1MB entry point)
├── makefile           Build configuration
├── src/
│   ├── kernel.c       Main kernel entry point (kernel_main)
│   ├── shell.c        Interactive shell with command dispatcher
│   ├── vga.c          VGA text mode driver (80x25 display)
│   ├── keyboard.c     PS/2 keyboard input handler
│   └── hw_io.c        Hardware port I/O (outb/inb utilities)
├── include/
│   ├── shell.h
│   ├── vga.h
│   ├── keyboard.h
│   └── hw_io.h
└── iso/               GRUB bootable ISO directory (created by `make iso`)
```

### Runtime Flow

1. **Boot** — `boot.asm` provides Multiboot header and calls `kernel_main()`
2. **Initialization** — Kernel clears VGA screen and starts the shell
3. **Shell** — Displays login prompt (password: 'r'), then command prompt
4. **Command Loop** — Reads keyboard input, executes built-in commands, repeats

---

## Building

### Requirements

- `gcc` — 32-bit capable C compiler (`gcc -m32`)
- `as` (GNU Assembler) — For x86 assembly (`as --32`)
- `ld` (GNU Linker) — With 32-bit support (`ld -m elf_i386`)
- `grub-mkrescue` — For creating bootable ISO (optional)
- `qemu-system-i386` or `qemu-system-x86_64` — For testing (optional)

### Compile

```bash
make           # Build Arx.bin kernel binary
make clean     # Remove build artifacts
```

### Create Bootable ISO

```bash
make iso       # Creates ArxOS.iso with GRUB bootloader
```

### Test in Emulator

```bash
# Run kernel directly (Multiboot mode)
make run

# Run ISO in QEMU x86_64 emulator
make run-iso
```

---

## Shell Commands

After boot and password entry, the shell accepts:

| Command | Description |
|---------|-------------|
| `help`  | Show available commands |
| `clear` | Clear the screen |
| `about` | Display OS and kernel version info |
| `ping`  | Echo "pong" (test command) |

---

## Known Limitations

- **No UEFI Support** — BIOS/Legacy mode only
- **No Memory Management** — No paging or virtual memory
- **No Interrupts** — Limited hardware interaction
- **Single-threaded** — No process/thread scheduling
- **No Filesystem** — No disk I/O beyond boot
- **Minimal Command Set** — Basic shell with hardcoded commands

---

## Learning Resources

This project is educational. Key concepts:

- **Bootloaders & Multiboot** — How kernels boot and receive control
- **x86 Protected Mode** — 32-bit CPU mode fundamentals
- **VGA Text Mode** — Direct hardware memory access for display
- **Hardware Port I/O** — Reading/writing to I/O ports
- **Linker Scripts** — Memory layout and section placement
- **Assembly & C Integration** — Calling conventions and cross-language boundaries

---

## Future Ideas

- [ ] Interrupt handling and timer
- [ ] Memory management (paging, heap)
- [ ] File system support
- [ ] Process/task management
- [ ] Expanded command set
- [ ] UEFI boot support

---

## License

GNU GPL v3.0

---

## Contact

Created by MasterArd. For questions or suggestions, open an issue on GitHub.
