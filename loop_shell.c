#include "main.h"

/**
 * shell_loop - the function that contains the shell loop
 * @var: var_t struct
 * Return: void
 */
void shell_loop(var_t *var)
{
	char *command;
	size_t length;

	while (1)
	{
		write(STDIN_FILENO, "$ ", 3);
		command = get_command(var);

		length = strlen(command) - 1;
		check_and_execute_cmd(command, var, length);
	}
}

/**
 * check_and_execute_cmd - the function that verifys the command and execute it
 * @cmd: command to check and run
 * @var: var_t structure
 * @length: length of the command
 * Return: void
 */

void check_and_execute_cmd(char *cmd, var_t *var, size_t length)
{
	if (strcmp(cmd, "\n") == 0 || strspn(cmd, " ") == length)
	{
		free(cmd);
		var->cmd_num++;
		return;
	}

	cmd = remove_comment(cmd);
	if (cmd)
	{
		if (check_command(cmd) != -1)
		{
			cmd = command_sub(cmd);
			if (!cmd)
			{
				var->cmd_num++;
				free(cmd);
				return;
			}
			var->sep = get_next_separator(cmd);
			var->cmd = cmd;
			execute_commands(var->cmd, var);
		}
		free(cmd);
	}
	var->cmd_num++;
}
