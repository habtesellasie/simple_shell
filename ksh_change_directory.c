#include "main.h"

/**
*ksh_cd - the function that has cd builtin command
*@argv: arguments to cd
*@var: var_t struct
*Return: Nothing
*/

int ksh_cd(char **argv, var_t *var)
{
	char *directory, *old_directory;

	if (!argv[1] || strspn(argv[1], "-") == 2)
	{
		directory = _getenv("HOME");
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		directory = _getenv("OLDPWD");
		if (!directory)
		{
			fprintf(stderr, "%s: cd: OLDPWD not set\n", var->shell_name);
			return (2);
		}
		fprintf(stdout, "%s\n", directory);
	}
	else
	{
		if (strspn(argv[1], "-") > 2)
			return (error_cd(argv, var, 1));

		directory = argv[1];
	}
	old_directory = getcwd(NULL, 0);
	if (setenv("OLDPWD", old_directory, 1) == -1)
		perror("set");

	if (chdir(directory) == -1)
	{
		free(old_directory);
		return (error_cd(argv, var, 0));
	}
	directory = getcwd(NULL, 0);
	if (setenv("PWD", directory, 1) == -1)
		perror("set");
	free(old_directory);
	free(directory);
	return (0);
}
