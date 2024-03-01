#include "main.h"

/**
 * _ourexit - function that exits the shell
 * @info: Structure containing possible arguments which is
 *      : Used to maintain constant function prototype.
 * Return: exit with a given exit status
 *        : 0 if info.argv[0] != "exit"
 */
int _ourexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _ourcd - function that changes the current directory of the process
 * @info: Structure containing possible argument which is
 *      :Used to maintain constant function prototype
 *  Return: Always 0
 */
int _ourcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can not cd int to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhelp - function that displays help of the shell
 * @info: Structure containing possibel argument which is 
 *      : Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _ourhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts(" Look at all possibelshell built in commands\n");
	_puts("	 help[BUILTIN NAME]\n");
	_puts("	  see spesfice information on each builtiin commands\n");
	if (0)
		_puts(*arg_array);
	return (0);
}


/**
 * _ourhistory - function displays the history list, one command by line,
 *          - preceded with line number starting at 0.
 * @info: Structure containing possible arguments which is
 *       : Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _ourhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * set_info - function that initializes info_t struct
 * @info: pointer the struct address
 * @av: the argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}