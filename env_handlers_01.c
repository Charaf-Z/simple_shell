#include "main.h"

/**
 * get_env - Searches for an environment variable by name.
 * @info: Pointer to the info_t struct.
 * @name: The name of the environment variable to search for.
 * Return: a pointer to the matched variable or NULL
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *s;

	while (node)
	{
		s = start_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Sets an environment variable in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @var: The environment variable name.
 * @value: The value to set for the environment variable.
 * Return: 0 on success, 1 on failure.
 */
int set_env(info_t *info, char *var, char *value)
{
	char *env_var = NULL;
	list_t *node;
	char *equal_sign_pos;

	if (!var || !value)
		return (0);
	env_var = malloc(str_length(var) + str_length(value) + 2);
	if (!env_var)
		return (1);
	str_n_cpy(env_var, var, str_length(var));
	str_n_cat(env_var, "=", str_length("="));
	str_n_cat(env_var, value, str_length(value));
	for (node = info->env; node; node = node->next)
	{
		equal_sign_pos = start_with(node->str, var);
		if (equal_sign_pos && *equal_sign_pos == '=')
		{
			free(node->str);
			node->str = env_var;
			info->env_changed = 1;
			return (0);
		}
	}
	add_node_end(&(info->env), env_var, 0);
	free(env_var);
	info->env_changed = 1;
	return (0);
}

/**
 * user_env - Prints the contents of the environment list.
 * @info: Pointer to the info_t struct.
 * Return: 0 after printing.
 */
int user_env(info_t *info)
{
	print_list_string(info->env);
	return (0);
}

/**
 * get_environ - Retrieves the environment strings from info_t.
 * @info: Pointer to the info_t struct.
 * Return: Pointer to the cached environment strings.
 */
char **get_environ(info_t *info)
{
	if (!info->env_strings || info->env_changed)
	{
		info->env_strings = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->env_strings);
}
