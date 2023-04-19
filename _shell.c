#include "shl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
/**
 * main - shell entry point
 * Return: 1 for success | 0 for failer
 */
int main(void)
{
	size_t size = 30;
	char *prompt = "shell 2 $ :";
	char *str_buffer;
	char *_argv[10];

	while (1)
	{
		str_buffer = (char *)malloc(sizeof(char) * size);
		printf("%s", prompt);

		if (getline(&str_buffer, &size, stdin) == -1)
		{
			perror("Error ");
			exit(EXIT_FAILURE);
		}

		generat_argv(str_buffer, _argv);

		if (execve(_argv[0], _argv, environ) == -1)
			perror(prompt);
	}

	return (0);
}

/**
 * generat_argv - generate command line agurments
 * @str_buffer: string to use to generat argv
 * @_argv: pointer to argv array of strings
 */
void generat_argv(char *str_buffer, char **_argv)
{
	str_buffer[strlen(str_buffer) - 1] = '\0';
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
