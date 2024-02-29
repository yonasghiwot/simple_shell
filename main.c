#include "main.h"
/**
 * main - simple shell entry point
 * Return: 0 on success
 */

int main(void)
{

	size_t len = 0;
	char *input = NULL, *value, *pathname, **argv;
	list_path *head = '\0';
	void (*f)(char **);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_puts("$ ");
		if (getline(&input, &len, stdin) == -1)
			break;
		argv = word_list(input, " \n");
		if (!argv || !argv[0])
			execute(argv);
		else
		{
			value = _getenv("PATH");
			head = linkpath(value);
			pathname = _which(argv[0], head);
			f = checkbuiltin(argv);
			if (f)
			{
				/*free(input);*/
				f(argv);
			}
			else if (!pathname)
				execute(argv);
			else if (pathname)
			{
				free(argv[0]);
				argv[0] = pathname;
				execute(argv);
			}
		}
	}
	free_list(head);
	freearv(argv);
	free(input);
	return (0);
}
