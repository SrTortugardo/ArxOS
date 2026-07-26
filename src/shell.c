#include "shell.h"
#include "vga.h"
#include "keyboard.h"

static int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

static void execute_command(const char *cmd)
{
    if (strcmp(cmd, "help") == 0)
    {
        print("Available commands:\n");
        print("  help  - Show this help message\n");
        print("  clear - Clear the screen\n");
        print("  about - Show OS details\n");
        print("  ping  - Returns Pong cuz why not\n");
    }
    else if (strcmp(cmd, "clear") == 0)
    {
        clear_screen();
    }
    else if (strcmp(cmd, "about") == 0)
    {
        print("ArxOS with Arcxzs Kernel v0.1 - Running in 32-bit Protected Mode.\n");
    }
    else if (strcmp(cmd, "ping") == 0)
    {
        print("pong\n");
    }
    else if (cmd[0] != '\0')
    {
        print("Unknown command: ");
        print(cmd);
        print("\n");
    }
}

void shell_run(void)
{
    char buffer[128];
    int buf_idx = 0;

    print("Shell started! Type 'help' for commands.\n\n");
    print("Started login process\n");
    print("Enter wompy ahh password:\n");

    while (1)
    {
        char c = getchar();
        if (c != 'r')
        {
            print("nu uhh\n");
        }
        else
        {
            print("you pressed the right key!\n");
            break;
        }
    }

    print("kernel> ");

    while (1)
    {
        char c = getchar();

        if (c == '\n')
        {
            putchar('\n');
            buffer[buf_idx] = '\0';
            execute_command(buffer);
            buf_idx = 0;
            print("kernel> ");
        }
        else if (c == '\b')
        {
            if (buf_idx > 0)
            {
                buf_idx--;
                backspace();
            }
        }
        else if (buf_idx < (int)sizeof(buffer) - 1)
        {
            buffer[buf_idx++] = c;
            putchar(c);
        }
    }
}
