#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "filesystem.h"
#include <stdint.h>

void kernel_main()
{
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    kprint("Type something, it will go through the kernel\n"
           "Type END to halt the CPU or PAGE to request a kmalloc()\n> ");

    kprintf("%s what the hell? %s %d %x", "bruh", "nah", 1234567890, 0xABCD);
}

void user_input(char *input)
{
    if (strcmp(input, "END") == 0)
    {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (strcmp(input, "PAGE") == 0)
    {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    }
    else if (strcmp(input, "PWD") == 0)
    {
        // kprintf("%s what the hell? %s", "bruh", "nah");
        // char *cwd;
        // get_cwd(cwd);
        // kprint(cwd);
    }
    kprint("\n> ");
}
