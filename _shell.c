#include "shl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - shell entry point
 * @ac: number comand line arguments
 * @av: array of strings
 * @env: environment variables
 * Return: 1 for success | 0 for failer
 */
int main(int ac, char **av, char **env)
{
	size_t size = 30;
	char *str_buffer;
	char *builtins[] = {"env", "exit", NULL};
	char *_argv[10];
	int chk_builtin_result;
	int pid;

	while (1)
	{
		str_buffer = (char *)malloc(sizeof(char) * size);
		if (ac > 1)
			perror("No arguments allowed...");

		printf(":) ");
		if (getline(&str_buffer, &size, stdin) == -1)
		{
			perror(av[0]);
			exit(EXIT_FAILURE);
		}

		generat_argv(str_buffer, _argv);
		chk_builtin_result = check_builtin(builtins, _argv[0]);
		if (chk_builtin_result >= 0)
		{
			run_builtin(builtins[chk_builtin_result], env);
		}
		else
		{
			if (check_command(_argv, "/bin/") == 1)
			{
				pid = fork();
				run_process(_argv, env, pid);
				wait(NULL);
			}
		}
	}
	if (pid > 0)
		free(str_buffer);

	return (0);
}
