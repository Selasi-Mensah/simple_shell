#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * 
 * Return: 0 on  success, 1 0n failure
*/
int main(int ac, char **av)
{
    myInfoType custominfo[] = { MY_CUSTOM_INIT };
    int file_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_d)
		: "r" (file_d));

    if (ac == 2)
    {
        file_d = open(av[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_print_error_string(av[0]);
				custom_print_error_string(": 0: Can't open ");
				custom_print_error_string(av[1]);
				custom_write_to_stderr('\n');
				custom_write_to_stderr(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		custominfo->read_file_descriptor = file_d;
	}
	listOfenviroment(custominfo);
	hist_read(custominfo);
	shell(custominfo, av);
	return (EXIT_SUCCESS);
}