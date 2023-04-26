#include "main.h"

/**
 * get_command - read command entered by user
 * @var: var_t struct
 * Return: the string that contains the command
 */
char *get_command(var_t *var)
{
	char *lign = NULL;
	size_t n = 0;

	if (getline(&lign, &n, stdin) == -1)
	{
		free(lign);
		if (feof(stdin))
		{
			free(var);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(var);
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	return (lign);
}
