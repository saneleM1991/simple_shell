#ifndef MAIN_H
#define MAIN_H

#include <dirent.h>
#include <sys/wait.h>

int str_split(char *str, char *delimiter, char **arr);
int chck_space(char *str);
void generat_argv(char *str_buffer, char **_argv);
int check_command(char **_argv, char *path);
int check_file(char *filename, DIR *dir);
int is_path(char *str);
void update_argv(char *command, char **_argv, char *path);
void _closedir(DIR *dir);
void _print_env(char **env);
int check_builtin(char **builtins, char *command);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
void _app_exit(void);
void run_builtin(char *str, char **env);
void run_process(char **_argv, char **env, pid_t pid);

#endif
