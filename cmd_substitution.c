#include "main.h"

int check_substitution(char *command);
int get_ppid(char *cmd, size_t *position);
char *_realloc(char *new_command, size_t *bufsize);
char *create_new_command(char *cmd);

/**
 * command_sub - the function makes command substitution for $$
 * @cmd: command string
 * Return: new command with substitution done or same command
 */
char *command_sub(char *cmd)
{
	char *new_command;

	if (check_substitution(cmd) == 1)
	{
		new_command = create_new_command(cmd);
		if (!new_command)
			return (NULL);
		return (new_command);
	}
	else
	{
		return (cmd);
	}
}

/**
 * create_new_command - the function that creates
 * new command by doing command substitution for $$
 * @cmd: command string
 * Return: New command with substitution done,
 * or NULL in case of an error
 */
char *create_new_command(char *cmd)
{
	size_t position, position_one, bufsize = BUF_SIZE;
	char *new_command;

	new_command = malloc(sizeof(char) * bufsize);
	if (!new_command)
	{
		perror("new_cmd");
		return (NULL);
	}
	position = position_one = 0;
	while (cmd[position] != '\n' && cmd[position] != '\0')
	{
		if (cmd[position] == '$' && cmd[position + 1] == '$')
		{
			if (get_ppid(new_command, &position_one) == 1)
			{
				free(new_command);
				return (NULL);
			}
			position++;
		}
		else
		{
			*(new_command + position_one) = cmd[position];
			position_one++;
		}
		position++;
		if (position_one >= bufsize)
		{
			new_command = _realloc(new_command, &bufsize);
			if (!new_command)
				return (NULL);
		}
	}
	*(new_command + position_one) = '\0';
	free(cmd);
	return (new_command);
}

/**
 * check_substitution - the function that checks
 * whether the command has the sub
 * @command: command to be check
 * Return: 1 if a substitution is to be done, 0 if there's none
 */
int check_substitution(char *command)
{
	int index = 0;

	while (command[index])
	{
		if (command[index] == '$')
			return (1);
		index++;
	}
	return (0);
}

/**
 * get_ppid - the function that gets the parent id
 * and append it to the command
 * @cmd: command to append the parent id
 * @position: index to start appending
 * Return: 0 on success, 1 on failure
 */
int get_ppid(char *cmd, size_t *position)
{
	pid_t par_id;
	char *par_id_str;

	par_id = getppid();
	par_id_str = convert_to_str(par_id);

	if (!par_id_str)
	{
		perror("ppid");
		return (1);
	}
	strcpy(cmd + *position, par_id_str);

	*position += strlen(par_id_str);
	free(par_id_str);

	return (0);
}

/**
 * _realloc - the fanction that reallocates new command string
 * in this case it doesn't fit the previous command
 * @new_command: command to reallocate
 * @bufsize: size of the command being reallocated
 * Return: New command string with reallocated memory
 */
char *_realloc(char *new_command, size_t *bufsize)
{
	*bufsize += BUF_SIZE;

	new_command = realloc(new_command, *bufsize);
	if (!new_command)
	{
		free(new_command);
		perror("new_cmd");
		return (NULL);
	}
	return (new_command);
}
