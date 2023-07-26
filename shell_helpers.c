#include "shl.h"
#include <stdio.h>
#include <unistd.h>

/**
 * generat_argv - generate command line agurments
 * @str_buffer: string to use to generat argv
 * @_argv: pointer to argv array of strings
 */
void generat_argv(char *str_buffer, char **_argv)
{
	str_buffer[_strlen(str_buffer) - 1] = '\0';
	if (chck_space(str_buffer) == 0)
	{
		_argv[0] = str_buffer;
		_argv[1] = '\0';
	}
	else
	{
		str_split(str_buffer, " ", _argv);
	}
}

/**
 * check_builtin - checks if the input is a built in command
 * @builtins: arry of builtins commands
 * @command: command to check
 * Return: return positive number if found
 */
int check_builtin(char **builtins, char *command)
{
	int i = 0;

	while (builtins[i] != NULL)
	{
		if (_strcmp(builtins[i], command) == 0)
			return (i);

		i++;
	}
	return (-1);
}

/**
 * run_builtin - run builtin command
 * @str: command to run
 * @env: environment variable for print_env
 */
void run_builtin(char *str, char **env)
{
	if (_strcmp(str, "exit") == 0)
	{
		_app_exit();
	}
	if (_strcmp(str, "env") == 0)
	{
		_print_env(env);
	}
}
/**
 * run_process - run programm in a child process
 * @_argv: command line arguments
 * @pid: process id
 * @env: environment variables
 */
void run_process(char **_argv, char **env, pid_t pid)
{
	if (pid == 0)
	{
		execve(_argv[0], _argv, env);
	}
}
