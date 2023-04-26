#include "main.h"

/**
 * remove_comment - removes comment from the command to be executed
 * @command: command to be executed
 * Return: the command without the comment
 */
char *remove_comment(char *command)
{
	size_t i = 0;

	while (command[i])
	{
		if (command[i] == '#')
		{
			if (i == 0)
			{
				free(command);
				return (NULL);
			}
			else if (isspace(command[i - 1]) || command[i - 1] == ';')
			{
				break;
			}
		}
		i++;
	}

	if ((i + 1) != strlen(command))
	{
		command = realloc(command, i + 1);
		command[i] = '\0';
	}

	return (command);
}
