#include "main.h"

/**
*ksh_exit - the function that terminates a process
*@argv: the stts
*@var: var_t struct
*Return: 0 if error does not occure, 127 if error occurs
*/

int ksh_exit(char **argv, var_t *var)
{
	int stats;

	if (!argv[1])
	{
		free(argv[0]);
		free(var);
		free(argv);
		exit(EXIT_SUCCESS);
	}
	else if (argv[1])
	{
		stats = convert_to_int(argv[1]);

		if (stats < 0)
			return (error_exit(argv, var));
		free(var);
		free(argv[0]);
		free(argv);
		exit(stats);
	}
	return (0);
}
