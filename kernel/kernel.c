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
        kprintf("%s\n", get_cwd());
    }

    // list all the other directories in the current directory
    else if (strcmp(input, "LS") == 0)
    {
        list_files();
    }

    // create a directory
    else if (starts_with(input, "MKDIR"))
    {
        char *file_name = substring(input, 6);

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

    // change directory
    else if (starts_with(input, "CD"))
    {

        char *file_name = substring(input, 3);

        if (strcmp(file_name, "") != 0)
        {
            change_directory(file_name);
        }
        else
        {
            kprint("Please specify a directory name\n");
        }
    }

    // delete directory
    else if (starts_with(input, "RM"))
    {
        char *file_name = substring(input, 3);

        if (strcmp(file_name, "") != 0)
        {
            delete_file(file_name);
        }
        else
        {
            kprint("Please specify a directory name\n");
        }
    }

    // rename directory
    else if (starts_with(input, "MV"))
    {
        char *names_with_space = substring(input, 3);

        char *old_name = (char *)kmalloc(256 * sizeof(char));
        // keep adding the characters to the old_name until we hit a space
        int i = 0;
        while (names_with_space[i] != ' ')
        {
            old_name[i] = names_with_space[i];
            i++;
        }

        // pick up where we left off for the new name
        char *new_name = (char *)kmalloc(256 * sizeof(char));
        int j = 0;
        i++; // skip the space
        while (names_with_space[i] != '\0')
        {
            new_name[j] = names_with_space[i];
            i++;
            j++;
        }

        if (strcmp(old_name, "") == 0)
        {
            kprintf("Please specify a directory name\n");
        }
        else if (strcmp(new_name, "") == 0)
        {
            kprintf("Please specify a new directory name\n");
        }
        else
        {
            rename_file(old_name, new_name);
        }
    }
    else
    {
        kprint("Unknown command :(\n");
    }
    kprint("> ");
}
