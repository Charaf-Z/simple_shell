#include "main.h"

/**
 * print_chr_fd - Writes a character to a specified file descriptor.
 * @character: The haracterharacter to be written.
 * @fd: The file descriptor to write to.
 * Return: On success, returns 1. Otherwise, returns -1.
 */
int print_chr_fd(const char character, int fd)
{
	static int i;
	static char buf[BUF_SIZE];

	if (character == EOF || i >= BUF_SIZE)
		write(fd, buf, i), i = 0;
	if (character != EOF)
		buf[i++] = character;
	return (1);
}

/**
 * print_str_fd - Writes a string to a specified file descriptor.
 * @string: The input string.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_str_fd(const char *string, int fd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
		i += print_chr_fd(*string++, fd);
	return (i);
}

