#include "shell.h"

/**
 * isinteractive - checking if shell is in the interactive mode
 * @info: infor structure
 * Return: 1 = interactive mode, 0 = not interactive
 */
int isinteractive(infor_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @chr: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char chr, char *del)
{
	while (*del)
		if (*del++ == chr)
			return (1);
	return (0);
}

/**
 *_isalpha - check if char is an alpha
 *@char_code: char to check
 *Return: 1 if is alpha / 0 if not
 */
int _isalpha(int char_code)
{
	if ((char_code >= 'a' && char_code <= 'z') ||
		(char_code >= 'A' && char_code <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converting a string to integer
 *@str: string to convert
 *Return: 0 if no numbers / otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
