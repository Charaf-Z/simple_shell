#include "main.h"

/**
 * print_err_char - Writes a character to the standard error output.
 * @c: The character to be written.
 * Return: On success, returns 1. Otherwise, returns -1.
 */
int print_err_char(int c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == EOF || i >= BUF_SIZE)
		write(2, buf, i), i = 0;
	if (c != EOF)
		buf[i++] = (char) c;
	return (1);
}

/**
 * print_err_string - Writes a string to the standard error output.
 * @s: The input string.
 */
void print_err_string(const char *s)
{
	if (!s)
		return;
	while (*s)
		print_err_char(*s++);
}
