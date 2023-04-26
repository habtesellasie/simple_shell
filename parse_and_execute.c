#include "main.h"

/**
 * parse_and_exec - executes commands as given by user
 * @commands: NULL terminated array of parsed commands
 * @var: var_t structure
 * Return: 0 if not fail, -1 if fail
 */
int parse_and_exec(char **commands, var_t *var)
{
	int i = 0;
	char *command = NULL;

	while (commands[i])
	{
		if (i == 0)
		{
			if (_exec(commands[i], var) == -1)
				return (-1);
		}
		else
		{
			command = commands[i];
			var->sep = get_next_separator(command);
			if (var->sep != NONE)
			{
				if (execute_commands(command, var) == -1)
					return (-1);
			}
			else
			{
				if (_exec(command, var) == -1)
					return (-1);
			}
		}
		i++;
	}
	return (0);
}


/**
 * _exec - the function that executes a single command depending on the next
 * separator
 * @command: to excute the command
 * @var: var_t struct
 * Return: 0 if not fail, -1 if fail
 */
int _exec(char *command, var_t *var)
{
	char **cmds = parse_command(command);

	switch (var->sep)
	{
	case NONE:
		if (execute_builtin(cmds, var) == -1)
			execute_single_command(cmds, var);
		break;
	case SEMICOLON:
		if (execute_builtin(cmds, var) == -1)
			execute_single_command(cmds, var);
		break;
	case AND:
		if (execute_builtin(cmds, var) == -1)
		{
			if (execute_single_command(cmds, var) == -1)
			{
				free(cmds);
				return (-1);
			}
		}
		break;
	case OR:
		if (execute_builtin(cmds, var) == -1)
		{
			if (execute_single_command(cmds, var) != -1)
			{
				free(cmds);
				return (-1);
			}
		}
		break;
	}
	free(cmds);
	return (0);
}
