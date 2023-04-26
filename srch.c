#include "main.h"

/**
 * search_path - the function searches the absolute
 * filepath for the program entered
 * @filename: the name of the program to search for
 * Return: Full path to the program if found - or NULL if it's not
 */
char *search_path(char *filename)
{
	char *path, *filepath, **paths;
	int position = 0;

	path = _getenv("PATH");
	paths = parse_path(path);

	while (paths[position])
	{
		struct stat st;

		filepath = get_abs_path(paths[position], filename);

		if (!filepath)
		{
			exit_search_safe(paths, filepath);
			return (NULL);
		}

		if (stat(filepath, &st) == 0)
		{
			free(paths[0]);
			free(paths);
			return (filepath);
		}
		position++;
		free(filepath);
	}
	free(paths[0]);
	free(paths);
	return (NULL);
}

/**
 * get_abs_path - appends the program name to the given directory
 * @filedir: PATH directory
 * @filename: the name of the program
 * Return: the generated absolute path to the program
 */
char *get_abs_path(char *filedir, char *filename)
{
	char *filepath;

	filepath = strdup(filedir);
	if (!filepath)
		return (NULL);

	filepath = realloc(filepath, (strlen(filepath) + strlen(filename) + 2));
	if (!filepath)
	{
		free(filepath);
		return (NULL);
	}

	strcat(filepath, "/");
	strcat(filepath, filename);

	return (filepath);
}

/**
 * parse_path - creates a NULL terminated array of the directories found in
 * the PATH environment variable
 * @path: PATH environment value variable
 * Return: NULL
 */
char **parse_path(char *path)
{
	size_t buffSize = BUF_SIZE, position = 0;
	char **tokens = malloc(sizeof(char *) * buffSize);
	char *localpath, *token;

	if (!tokens)
	{
		perror("parse_path: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	localpath = strdup(path);
	if (!localpath)
	{
		perror("parse_path: Memory allocation failed");
		free(tokens);
		exit(EXIT_FAILURE);
	}

	token = _strtok(localpath, ":");
	while (token)
	{
		tokens[position++] = token;
		token = _strtok(NULL, ":");

		if (position >= buffSize)
		{
			buffSize += BUF_SIZE;
			tokens = realloc(tokens, sizeof(char *) * buffSize);
			if (!tokens)
			{
				perror("Memory allocation failed");
				free(localpath);
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * exit_search_safe - the function that exits search safely
 * @paths: NULL terminated array of PATH directories
 * @filepath: absolute path to the program
 * Return: void
 */
void exit_search_safe(char **paths, char *filepath)
{
	free(paths[0]);
	free(paths);

	if (filepath)
		free(filepath);

	if (errno)
	{
		perror("search_path: memory allocation failure\n");
		exit(EXIT_FAILURE);
	}
}
