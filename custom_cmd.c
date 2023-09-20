#include "main.h"

/**
 * user_exit - Handles the exit command.
 * @info: Pointer to info_t struct.
 * Return: indicate the exit status.
 */
int user_exit(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _err_atoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			print_err_string(info->argv[1]);
			print_err_char('\n');
			return (1);
		}
		info->err_num = exit_code;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * user_cd - Handles the "cd" command.
 * @info: Pointer to info_t struct.
 * Return: On success, returns 1. Otherwise, returns -1.
 */
int user_cd(info_t *info)
{
	char *current_dir, *dir, buffer[BUF_SIZE];
	int chdir_ret;

	current_dir = getcwd(buffer, BUF_SIZE);
	if (!current_dir)
		print_string("Error: Failed to retrieve current directory\n");
	if (!info->argv[1])
	{
		chdir_ret = get_env(info, "HOME=") ?
				chdir(get_env(info, "HOME=")) :
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			print_string(current_dir), print_char('\n');
			return (1);
		}
		print_string(get_env(info, "OLDPWD=")), print_char('\n');
		chdir_ret =
				chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "Unable to change directory to ");
		print_err_string(info->argv[1]), print_err_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, BUF_SIZE));
	}
	return (0);
}

/**
 * user_help - Display help information about the shell.
 * @info: Unused parameter (suppressed warning).
 * Return: Always 0.
 */
int user_help(__attribute__((unused)) info_t *info)
{
	print_string("help function is not yet implemented.\n");
	return (0);
}

/**
 * user_history - Display the history of commands.
 * @info: Pointer to the shell's information struct.
 * Return: Always 0.
 */
int user_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

