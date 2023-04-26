#include "main.h"
/**
*_strtok - the function tokenize a string
*@str: string to tokenize
*@delim: the delimiter
*Return: tokens
*/

char *_strtok(char *str, const char *delim)
{
	static char *buffer = "";
	char *tokn, *seas1;
	char **ptrsave = &buffer;

	tokn = str ? str : *ptrsave;
	tokn += strspn(tokn, delim);
	if (*tokn == '\0')
	{
		*ptrsave = "";
		return (NULL);
	}

	seas1 = tokn + strcspn(tokn, delim);
	if (*seas1 != '\0')
		*seas1++ = '\0';

	*ptrsave = seas1;
	return (tokn);
}

