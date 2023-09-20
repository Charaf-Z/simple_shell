#include "main.h"

/**
 * str_n_cpy - function that copies a string
 * @dest: destination string
 * @src: source string
 * @length: number of bytes of @src
 * Return: @dest
 */
char *str_n_cpy(char *dest, const char *src, size_t length)
{
	size_t i;

	for (i = 0; i < length - 1 && src[i] != '\0'; i++)
		dest[i] = src[i];
	while (i < length)
		dest[i++] = '\0';
	return (dest);
}

/**
 * str_n_cat - function that concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @length: most number bytes from src
 * Return: @dest
 */
char *str_n_cat(char *dest, const char *src, int length)
{
	int len = str_length(dest), i;

	for (i = 0; i < length && src[i]; i++)
		dest[len + i] = src[i];
	if (i < length)
		dest[len + i] = '\0';
	return (dest);
}

/**
 * str_chr - function that locates a character in a string
 * @string: the string to search in
 * @character: the character to search for
 * Return: the pointer to the first occurrence or null
 */
char *str_chr(char *string, const char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}

/**
 * dup_str - Duplicate a substring of characters from @string.
 * @string: Source string.
 * @start: Index to start copying from.
 * @end: Index to stop copying at.
 * Return: Pointer to the duplicated substring.
 */
char *dup_str(const char *string, int start, int end)
{
	int i, k;
	char *buf = malloc(BUF_SIZE);

	_memset((void *)buf, 0, BUF_SIZE);
	if (!buf)
		return (NULL);
	for (i = start, k = 0; i < end && k < BUF_SIZE - 1; i++)
		if (string[i] != ':')
			buf[k++] = string[i];
	buf[k] = '\0';
	return (buf);
}
