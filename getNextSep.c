#include "main.h"

/**
 * get_next_separator - the function that gets next separator in the command
 * @cmd: the command as entered by user
 * Return: the next separator found
 */
Separator get_next_separator(const char *cmd)
{
	while (*cmd++)
	{
		if (*cmd == ';')
			return (SEMICOLON);
		else if (*cmd == '&')
			return (AND);
		else if (*cmd == '|')
			return (OR);
	}
	return (NONE);
}
