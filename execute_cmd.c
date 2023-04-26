#include "main.h"

/**
 * execute_single_command - the function that executes a single command
 * by calling a child process
 * @argv: array of arguments
 * @var: var_t struct
 * Return: -1 if fail, 0 if not
 */
int execute_single_command(char **argv, var_t *var)
{
	char *program_name;

	program_name = check_program_name(argv[0]);
	if (program_name)
	{
		return (run_child(program_name, argv, environ));
	}
	else
	{
		error_not_found(argv[0], var);
		return (-1);
	}

	return (0);
}

/**
 * run_child - the function that forks and executes a child process
 * @program_name: the name of the program to execute
 * @argv: array of arguments
 * @envp: environment variables
 * Return: -1 if fail, 0 if not
 */
int run_child(char *program_name, char **argv, char **envp)
{
	pid_t child_process;
	int stats;

	child_process = fork();
	if (child_process == -1)
	{
		perror("ksh");
		return (-1);
	}
	if (child_process == 0)
	{
		if (execve(program_name, argv, envp) == -1)
		{
			perror("ksh");
			free(program_name);
			free(argv);
			return (-1);
		}
	}
	else
	{
		do {
			waitpid(-1, &stats, WUNTRACED);
		} while (!WIFEXITED(stats) && !WIFSIGNALED(stats));
		free(program_name);
	}
	return (0);
}
