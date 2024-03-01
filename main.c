#include "main.h"

/**
* handle_EOF - handles the End of File
* @len: return value of getline function
* @input: input coming from user
 */
void handle_EOF(int len, char *input)
{
	(void)input;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(input);
		}
		exit(0);
	}
}
/**
  * _isatty - a function that checks keyboard input
  * returns nothing
  */

void _isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}
/**
 * main - entry point of main Shell
 * Return: 0 on success
 */

int main(void)
{
	ssize_t len = 0;
	char *input = NULL;
	char *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **);

	while (len != EOF)
	{
		_isatty();
		len = getline(&input, &size, stdin);
		handle_EOF(len, input);
		arv = word_list(input, " \n");
		if (!arv || !arv[0])
			execute(arv);
		else
		{
			value = _getenv("PATH");
			head = linkpath(value);
			pathname = _which(arv[0], head);
			f = checkbuiltin(arv);
			if (f)
			{
				/*free(input);*/
				f(arv);
			}
			else if (!pathname)
				execute(arv);
			else if (pathname)
			{
				/*free(arv[0]);*/
				arv[0] = pathname;
				execute(arv);
			}
		}
	}
	free_list(head);
	freearv(arv);
	free(input);
	return (0);
}
