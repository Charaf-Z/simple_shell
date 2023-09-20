#include "main.h"

/**
 * convert_number - Convert a number to
 *	a string representation in a given base.
 * @nbr: The number to be converted.
 * @base: The base to use for conversion.
 * @flags: Flags to control conversion behavior.
 * Return: A pointer to the string representation of the converted number.
 */
char *convert_number(long int nbr, int base, int flags)
{
	static char buffer[50];
	char *p_nbr = &buffer[49];
	static char *array;
	unsigned long n = (nbr < 0 && !(flags & TO_UNSIGNED)) ? -nbr : nbr;

	*p_nbr = '\0';
	array = (flags & TO_LOWER) ? "0123456789abcdef" : "0123456789ABCDEF";
	do {
		*--p_nbr = array[n % base];
		n /= base;
	} while (n != 0);
	if (!(flags & TO_UNSIGNED) && nbr < 0)
		*--p_nbr = '-';
	return (p_nbr);
}

/**
 * remove_comments - Removes comments from a string.
 * @buf: The input string.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
