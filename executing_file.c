#include "main.h"

char *get_command_line(int file_dr, char *c);

/**
 * execute_file_cmd - the function that executes commands in a file. 
 * The file has a single command on each line.
 * Every command should be on its own line and file must have blank line at end
 * @filename: name of the file
 * @var: var_t structure
 * Return: 0 if success, -1 if file cannot be accessed, else 1 
 */
int execute_file_cmd(char *filename, var_t *var)
{
	int file_dr, row_bytes;
	size_t length;
	char c, *cmd;

	file_dr = open(filename, O_RDONLY);
	if (file_dr == -1)
		return (-1);

	row_bytes = read(file_dr, &c, sizeof(char));
	if (row_bytes == 0 || row_bytes == -1)
		return (1);

	while (c != EOF && row_bytes != -1 && row_bytes != 0)
	{
		while (c == '\n')
		{
			var->cmd_num++;
			row_bytes = read(file_dr, &c, sizeof(char));
			if (c == EOF || row_bytes == -1)
			{
				close(file_dr);
				return (1);
			}
		}
		cmd = get_command_line(file_dr, &c);
		if (!cmd)
		{
			perror("");
			close(file_dr);
			return (1);
		}
		length = strlen(cmd);
		check_and_execute_cmd(cmd, var, length);
		row_bytes = read(file_dr, &c, sizeof(char));
		if (row_bytes < 0)
		{
			return (0);
		}
	}
	close(file_dr);
	return (0);
}

/**
 * get_command_line - the funciton that reads command from file
 * @file_dr: file descriptor of the file to read
 * @c: pointer to the last read character
 * Return: string containing the command to execute
 */
char *get_command_line(int file_dr, char *c)
{
	char *cmd;
	int row_bytes;
	size_t bufsize = BUF_SIZE, pos;

	cmd = malloc(sizeof(char) * bufsize);
	if (!cmd)
		return (NULL);

	for (pos = 0; *c != '\n' && *c != EOF; pos++)
	{
		printf("TWO\n");
		printf("c2: %d\n", *c);
		if (pos >= bufsize)
		{
			bufsize += BUF_SIZE;
			cmd = realloc(cmd, bufsize);
			if (!cmd)
			{
				free(cmd);
				return (NULL);
			}
		}

		*(cmd + pos) = *c;
		row_bytes = read(file_dr, c, sizeof(char));
		if (row_bytes == -1)
		{
			free(cmd);
			return (NULL);
		}
	}
	*(cmd + pos) = '\0';

	return (cmd);
}
