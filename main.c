#include "main.h"

/**
 * main - entry point
 * @argc: count argument
 * @argv: vector argument
 * Return: 0 if not fail, 1 if fail
 */
int main(int argc, char **argv)
{
	var_t *shell_variable = initialize_shell_var(argv, environ);

	if (!shell_variable)
		return (1);

	if (argc > 1)
	{
		if (execute_file_cmd(argv[1], shell_variable) == -1)
		{
			int stat;

			stat = error_opening_file(argv[1], shell_variable);
			free(shell_variable);
			return (stat);
		}
	}
	else
	{
		signal(SIGINT, handle_signal_2);
		shell_loop(shell_variable);
	}

	free(shell_variable);
	return (0);
}
