#include "main.h"

/**
 * str_to_word - Splits a string into words based on delimiters.
 * @string: The input string.
 * @delimiter: The string containing delimiters.
 * Return: A dynamically allocated array of strings, or NULL on failure.
 */
char **str_to_word(const char *string, char *delimiter)
{
	int nbr_words, i, j, k, m;
	char **str = NULL;

	if (!string || string[0] == '\0')
		return (NULL);
	delimiter = !delimiter ? " " : delimiter;
	nbr_words = num_words(string, delimiter);
	if (!nbr_words)
		return (NULL);
	str = malloc((nbr_words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0, k = 0; i < nbr_words; i++)
	{
		while (is_delimiter(string[j], delimiter))
			j++;
		while (!is_delimiter(string[j + k], delimiter) && string[j + k] != '\0')
			k++;
		str[i] = malloc((k + 1) * sizeof(char));
		if (!str[i])
		{
			for (k = 0; k < i; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str[i][m] = string[j++];
		str[i][m] = '\0';
	}
	str[i] = NULL;
	return (str);
}

/**
 * num_words - Counts the number of words in a string.
 * @string: The input string.
 * @delimiter: The string containing delimiters.
 * Return: The number of words.
 */
int num_words(const char *string, const char *delimiter)
{
	int i = 0, nbr_words = 0;

	for (; string[i] != '\0'; i++)
		if (!is_delimiter(string[i], delimiter) &&
		(is_delimiter(string[i + 1], delimiter) || string[i + 1] == '\0'))
			nbr_words++;
	return (nbr_words);
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiter: The string containing delimiters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(const char character, const char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}
