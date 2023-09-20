#include "main.h"

/**
 * print_alias - Print an alias.
 * @node: Pointer to the alias node to be printed.
 * Return: 0 if the alias was successfully printed, 1 if the node is NULL.
 */
int print_alias(list_t *node)
{
	char *equal_sign_pos = NULL, *a = NULL;

	if (node)
	{
		equal_sign_pos = str_chr(node->str, '=');
		for (a = node->str; a <= equal_sign_pos; a++)
			print_char(*a);
		print_char('\'');
		print_string(equal_sign_pos + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * unset_alias - Unset an alias.
 * @info: Pointer to the shell's information struct.
 * @s: The alias to be unset.
 * Return: 1 on success, 0 if alias is not found.
 */
int unset_alias(info_t *info, char *s)
{
	char *equal_sign_pos, c;
	int result;

	equal_sign_pos = str_chr(s, '=');
	if (!equal_sign_pos)
		return (1);
	c = *equal_sign_pos;
	*equal_sign_pos = '\0';
	result = delete_node_at_index(&(info->alias),
	  get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*equal_sign_pos = c;
	return (result);
}

/**
 * set_alias - Set or modify an alias.
 * @info: Pointer to the shell's information struct.
 * @str: The alias to be set or modified.
 * Return: 1 on success, 0 on failure.
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign_pos;

	equal_sign_pos = str_chr(str, '=');
	if (!equal_sign_pos)
		return (1);
	if (!*++equal_sign_pos)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * user_alias - Handle alias commands.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int user_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_pos = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		for (node = info->alias; node; node = node->next)
			print_alias(node);
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_pos = str_chr(info->argv[i], '=');
		if (equal_sign_pos)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
