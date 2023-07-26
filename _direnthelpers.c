#include "shl.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/**
 * check_command - checks if command exist
 * @_argv: command to check
 * @path: the directory where will check the command
 * Return: 1 command fount | 0 command not found
 */
int check_command(char **_argv, char *path)
{
	DIR *directory;
	char *temp_arr[10];

	directory = opendir(path);

	if (is_path(_argv[0]) == 1)
	{
		str_split(_argv[0], "/", temp_arr);
		if (check_file(temp_arr[1], directory))
		{
			update_argv(temp_arr[1], _argv, path);
			return (1);
		}
		return (0);
	}

	if (check_file(_argv[0], directory))
	{
		update_argv(_argv[0], _argv, path);
		return (1);
	}
	return (0);
}

/**
 * update_argv - update argv[0] to a full path of the command
 * @command: shell command
 * @_argv: pointer to argv
 * @path: path to command
 */
void update_argv(char *command, char **_argv, char *path)
{
	char *str = (char *)malloc(20);

	strcpy(str, path);
	strcat(str, command);

	free(_argv[0]);
	_argv[0] = str;
}

/**
 * _closedir - close open directory
 * @dir: directry to close
 */
void _closedir(DIR *dir)
{
	if (closedir(dir) == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
}
/**
 * check_file - check an exe file in a directory
 * @filename: filename to check
 * @dir: directory to check to
 * Return: 1 file found | 0 file not found
 */
int check_file(char *filename, DIR *dir)
{
	struct dirent *entry;

	if (dir == NULL)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, filename) == 0)
		{
			_closedir(dir);
			return (1);
		}
	}

	closedir(dir);
	return (0);
}
