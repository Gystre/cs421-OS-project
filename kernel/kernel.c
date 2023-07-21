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

    kprintf("%s no way is that? %s %d %x\n", "bruh", "nah", 1234567890, 0xABCD);

    // create the root folder
    init_file_system();

    kprint("\n> ");
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
        uint32_t page = kmalloc_ex(1000, 1, &phys_addr);
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
        char *cwd;
        get_cwd(cwd);
    }
    else if (strcmp(input, "LS") == 0)
    {
        list_files();
    }
    else if (starts_with(input, "MKDIR"))
    {
        char file_name[] = "";
        substring(input, 6, file_name);

        if (strcmp(file_name, "") != 0)
        {
            kprintf("Creating directory %s\n", file_name);
            create_file(file_name);
        }
        else
        {
            kprint("Please specify a directory name\n");
        }
    }
    else
    {
        kprint("Unknown command\n");
    }
    kprint("> ");
}
