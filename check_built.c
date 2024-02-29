#include "main.h"

/**
* checkbuiltin - checks if the command is a builtin
* @arv: array of arguments
* Return: a pointer to function that takes argv and returns void
*/
void(*checkbuiltin(char **arv))(char **arv)
{
	int i, j;
	builtin List[] = {
		{"exit", exit_shell},
		{"env", env},
		{NULL, NULL}
	};

	for (i = 0; List[i].name; i++)
	{
		j = 0;
		if (List[i].name[j] == arv[0][j])
		{
			for (j = 0; arv[0][j]; j++)
			{
				if (List[i].name[j] != arv[0][j])
					break;
			}
			if (!arv[0][j])
				return (List[i].func);
		}
	}
	return (0);
}
