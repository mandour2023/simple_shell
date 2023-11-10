#include "custom_shell.h"

/**
 * custom_main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int custom_main(int argc, char **argv)
{
    custom_info_t information[] = { CUSTOM_INFO_INIT };
    int file_descriptor = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (file_descriptor)
        : "r" (file_descriptor));

    if (argc == 2)
    {
        file_descriptor = open(argv[1], O_RDONLY);
        if (file_descriptor == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _custom_puts(argv[0]);
                _custom_puts(": 0: Can't open ");
                _custom_puts(argv[1]);
                _custom_putchar('\n');
                _custom_putchar(CUSTOM_BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        information->read_fd = file_descriptor;
    }
    custom_populate_env_list(information);
    custom_read_history(information);
    custom_shell(information, argv);
    return (EXIT_SUCCESS);
}
