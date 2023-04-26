#include "main.h"

/**
 * parse_command - the function that does token size of the command entered
 * @command: to parse a command
 * Return: Array of tokens if not fail or NULL on fail
 */
char **parse_command(char *command)
{
	size_t bufsize = BUF_SIZE, i;
	char **tkns, *tkn;

	if (!command)
		return (NULL);

	tkns = malloc(bufsize * sizeof(char *));
	if (!tkns)
	{
		perror("Failed to allocate memory");
		free(command);
		exit(EXIT_FAILURE);
	}

	tkn = _strtok(command, " \n");

	i = 0;
	while (tkn != NULL)
	{
		tkns[i++] = tkn;
		tkn = _strtok(NULL, " \n");

		if (i >= bufsize)
		{
			bufsize += BUF_SIZE;
			tkns = realloc(tkns, sizeof(char *) * bufsize);
			if (!tkns)
			{
				perror("Memory allocation failed");
				free(command);
				free(tkns);
				exit(EXIT_FAILURE);
			}
		}
	}
	tkns[i] = NULL;

	return (tkns);
}
