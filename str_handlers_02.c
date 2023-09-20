#include "main.h"

/**
 * start_with - Check if a string starts with a given prefix.
 * @string: The string to be checked.
 * @prefix: The prefix to be checked for.
 * Return: the next address after the prefix, or NULL.
 */
char *start_with(char *string, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *string++)
			return (0);
	return (string);
}

/**
 * str_dup - Duplicate a string.
 * @str: The string to be duplicated.
 * Return: A pointer to the newly allocated duplicated string.
 */
char *str_dup(const char *str)
{
	int len = 0;
	char *s;

	if (!str)
		return (NULL);
	s = malloc(sizeof(char) * (str_length(str) + 1));
	if (!s)
		return (NULL);
	for (; str[len]; len++)
		s[len] = str[len];
	s[len] = '\0';
	return (s);
}

/**
 * str_cmp - function that compares two strings
 * @str1: string to be compared
 * @str2: string to be compared
 * Return: 0 if true
 */
int str_cmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++, str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_rpl - Replaces the content of a string pointer with a new string
 * @old: Pointer to the old string
 * @new: New string to replace with
 * Return: Always returns 1
 */
int str_rpl(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * str_cat - Concatenate two strings.
 * @dest: The destination string.
 * @src: The source string to be appended.
 * Return: A pointer to the destination string.
 */
char *str_cat(char *dest, const char *src)
{
	int i = 0, j;

	i = str_length(dest);
	for (j = 0; src[j]; j++)
		dest[i++] = src[j];
	return (dest);
}
