#include "main.h"
/**
*_getenv - the function that gets envirnment variable
*@name: name of variable to get
*Return: the nevironment variable
*/
char *_getenv(const char *name)
{
	size_t position = 0;
	size_t len = strlen(name);

	if (!environ || !name || strcmp(name, "=") == 0)
		return (NULL);

	while (strncmp(name, environ[position], len) != 0)
	{
		if (environ[++position] == NULL)
			return (NULL);
	}

	if (environ[position])
		return (environ[position] + len + 1);

	return (NULL);
}
