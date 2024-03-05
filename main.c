#include "main.h"

/**
 * open_file - Opens a file if provided as a command-line argument
 * @info: Pointer to info_t structure
 * @ac: Argument count
 * @av: Argument vector
 */
void open_file(info_t *info, int ac, char **av)
{
	int fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			exit(EXIT_FAILURE);
		}
		info->readfd = fd;
	}
}

/**
 * setup_environment - Sets up environment for the shell
 * @info: Pointer to info_t structure
 */
void setup_environment(info_t *info)
{
	populate_env_list(info);
	read_history(info);
}

/**
 * handle_input - Handles user input
 * @info: Pointer to info_t structure
 * @av: Argument vector
 * @builtin_ret: Pointer to store the result of built-in command execution
 * @r: Pointer to store the result of input retrieval
 */
void handle_input(info_t *info, char **av, int *builtin_ret, ssize_t *r)
{
	clear_info(info);
	if (interactive(info))
		_puts("$ ");
	_eputchar(BUF_FLUSH);
	*r = get_input(info);
	if (*r != -1)
	{
		set_info(info, av);
		*builtin_ret = find_builtin(info);
		if (*builtin_ret == -1)
			find_cmd(info);
	}
	else if (interactive(info))
		_putchar('\n');
	free_info(info, 0);
}

/**
 * main - Program entry point
 * @ac: Argument count
 * @av: Argument vector
 * Return: Returns condition, 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;
	int builtin_ret = 0;
	ssize_t r = 0;

	asm (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd)
			);
	open_file(info, ac, av);
	setup_environment(info);
	while (r != -1 && builtin_ret != -2)
	{
		handle_input(info, av, &builtin_ret, &r);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (EXIT_SUCCESS);
}
