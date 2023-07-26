#include "shell.h"

/**
 * _exit - my built in exit shell
 * @info: Structure for potential arguments.
 *  Return: exits with status
 */
int _ext(infor_t *info)
{
	int ex_check;

	if (info->argv[1])
	{
		ex_check = _erratoi(info->argv[1]);
		if (ex_check == -1)
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
 * _cd - change current directory
 * @info: Structure for potential arguments
 *  Return: Always 0
 */
int _cd(infor_t *info)
{
	char *s, *dir, buffer[1024];
	int cdr_rt;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cdr_rt = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cdr_rt = chdir(dir);
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
		cdr_rt = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cdr_rt = chdir(info->argv[1]);
	if (cdr_rt == -1)
	{
		print_error(info, "can't cd to ");
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
 * _help - directory of the process
 * @info: Structure containing agruments
 *  Return:  0
 */
int _help(infor_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
