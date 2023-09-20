#include "main.h"

/**
 * check_chain - Modifies the buffer based on command chaining type and status
 * @info: Pointer to the info_t struct
 * @buf: Buffer containing the command line
 * @p: Pointer to the current position in the buffer
 * @i: Current index in the buffer
 * @len: Length of the buffer
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == AND_CMD && info->status)
		buf[i] = '\0', j = len;
	if (info->cmd_buf_type == OR_CMD && !info->status)
		buf[i] = '\0', j = len;
	*p = j;
}

/**
 * is_cmd - Check if a path corresponds to a command.
 * @info: Pointer to the info_t struct (not used in this function).
 * @path: Path to check.
 * Return: 1 if path is a command (regular file), 0 otherwise.
 */
int is_cmd(__attribute__((unused)) info_t *info, char *path)
{
	struct stat file_stat;

	if (!path || stat(path, &file_stat) != 0)
		return (0);
	return ((file_stat.st_mode & S_IFREG) ? 1 : 0);
}

/**
 * find_path - Find the full path of a command.
 * @info: Pointer to the info_t struct.
 * @path_str: Colon-separated list of directories.
 * @cmd: Command to search for.
 * Return: Pointer to the full path if found, NULL otherwise.
 */
char *find_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path = NULL;

	if (!path_str || !cmd)
		return (NULL);
	if (str_length(cmd) > 2 && start_with(cmd, "./"))
		if (is_cmd(info, cmd))
			return (cmd);
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_str(path_str, curr_pos, i);
			if (!*path)
				str_n_cpy(path, cmd, str_length(cmd));
			else
				str_n_cat(path, "/", str_length("/")),
				str_n_cat(path, cmd, str_length(cmd));
			if (is_cmd(info, path))
				return (path);
			if (!path_str[i])
			{
				free(path);
				break;
			}
			curr_pos = i + 1;
			free(path);
		}
		i++;
	}
	return (NULL);
}

/**
 * is_chain - Checks if the current command
 *	contains a command chaining operator.
 * @info: Pointer to the info_t structure.
 * @buf: Pointer to the command buffer.
 * @p: Pointer to the current position in the buffer.
 * Return: 1 if a chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
		buf[j++] = '\0', info->cmd_buf_type = OR_CMD;
	else if (buf[j] == '&' && buf[j + 1] == '&')
		buf[j++] = '\0', info->cmd_buf_type = AND_CMD;
	else if (buf[j] == ';')
		buf[j] = '\0', info->cmd_buf_type = CHAIN_CMD;
	else
		return (0);
	*p = j;
	return (1);
}
