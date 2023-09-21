#include "main.h"

/**
 * hsh - Main shell loop
 * @info: Pointer to info_t structure
 * @av: Array of strings containing command-line arguments
 * Return: Return value of the last executed built-in command
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			print_string("$ ");
		print_err_char(EOF);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			print_char('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Find and execute built-in commands
 * @info: Pointer to info_t structure
 * Return: Return value of the executed built-in command, or -1 if not found
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	built_in_t builtintbl[] = {
			{"exit", user_exit},
			{"env", user_env},
			{"help", user_help},
			{"history", user_history},
			{"setenv", user_setenv},
			{"unsetenv", user_unsetenv},
			{"cd", user_cd},
			{"alias", user_alias},
			{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Find and execute external commands
 * @info: Pointer to info_t structure
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
		info->line_count++, info->linecount_flag = 0;

	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n\a\r"))
			k++;
	if (!k)
		return;
	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
		info->path = path, fork_cmd(info);
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
			 || info->argv[0][0] == '/') &&
				is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "Not Found??\n");
		}
	}
}

/**
 * fork_cmd - Fork and execute external command
 * @info: Pointer to info_t structure
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (access(info->path, X_OK) != 0)
			print_err(info, "Permission denied!\n"), exit(126);
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
