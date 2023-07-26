#include "shl.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _print_env - printing environment variables
 * @env: invironment variables to print
 */
void _print_env(char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * _app_exit - exit application
 */
void _app_exit(void)
{
	exit(EXIT_SUCCESS);
}
