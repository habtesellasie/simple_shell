#include "main.h"

/**
 * split_commands - splits a command into two strings
 * @command: to split the command
 * @delim: set of bytes that delimits the tokens in command
 * Return: Null terminated array containing two strings
 * if not fail or NULL if fail
 */
char **split_commands(char *command, const char *delim)
{
	int position = 0;
	char *token;
	char **cmds = calloc(3, sizeof(char *));

	if (!cmds)
		return (NULL);

	token = _strtok(command, delim);
	cmds[position++] = token;

	token = _strtok(NULL, "\n\0");

	if (delim[0] == '|' || delim[0] == '&')
	{
		cmds[position++] = token + 1;
	}
	else
	{
		cmds[position++] = token;
	}
	cmds[position] = NULL;

	return (cmds);
}
