#include "shl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * str_split - split a string in to array of strings
 * @str: a string to split
 * @delimiter: charactor seperator
 * @arr: arry
 * Return: number of token
 */
int str_split(char *str, char *delimiter, char **arr)
{
	int i = 0;
	char *token;

	token = strtok(str, delimiter);

	while (token != NULL)
	{
		arr[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
		strncpy(arr[i], token, (strlen(token) + 1));
		token = strtok(NULL, delimiter);
		i++;
	}

	arr[i] = '\0';

	return (i);
}

/**
 * chck_space - check for spaces in a string
 * @str: string to search
 * Return: 1 if found | 0 no found
 */
int chck_space(char *str)
{
	while (*str != '\0')
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

/**
 * is_path - check if a string is path
 * @str: string to check
 * Return: 1 if is a path | 0 if it's not
 */
int is_path(char *str)
{
	while (*str != '\0')
	{
		if (*str == '/')
			return (1);

		str++;
	}
	return (0);
}
