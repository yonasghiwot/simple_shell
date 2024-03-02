#include "main.h"

/**
 * _ourenv - function that prints the current environment
 * @info: Structure containing possible arguments which is
 *      :Used to maintain constant function prototype.
 * Return: Always 0
 */
int _ourenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - function that gets the value of an enviroment variable
 * @info: Structure containing possibel arguments which is
 *       :Used to maintain
 * @name: env variable name
 * Return: the value of enviroment variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function Initialize a new environment variable,
 *            - or modify an existing one
 * @info: Structure containing posible arguments which is
 *      : Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function that Remove an environment variable
 * @info: Structure containing possible arguments which is
 *      : Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - function that populates env linked list
 * @info: Structure containing possibel arguments which is
 *      : Used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
