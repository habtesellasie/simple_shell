#include "main.h"

/**
 * initialize_shell_var - the function that initializes the var_t struct
 * @argv: argument vector
 * @envp: environment variable
 * Return: initialized var_t struct
 */
var_t *initialize_shell_var(char **argv, char **envp)
{
	var_t *n_shell = malloc(sizeof(var_t));

	if (!n_shell)
		return (NULL);

	strcpy(n_shell->shell_name, argv[0]);
	n_shell->cmd_num = 1;
	n_shell->env = envp;

	return (n_shell);
}
