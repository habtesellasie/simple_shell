#include "main.h"

/**
 * check_prog_name - the function that checks whether program given is valid
 * @filename: Name of the program to check or path to the program
 * Return: Path to the progrm or NULL if not found
 */
char *check_prog_name(char *filename)
{
	struct stat st;
	char *file_path;

	if (!filename)
		return (NULL);

	if (filename[0] == '.' && filename[1] == '/')
	{
		if (stat(filename + 2, &st) == 0)
			return (strdup(filename));
		else
			return (NULL);
	}
	else if (filename[0] == '/')
	{
		if (stat(filename, &st) == 0 && S_ISREG(st.st_mode))
		{
			return (strdup(filename));
		}
		else
		{
			return (NULL);
		}
	}

	file_path = search_path(filename);
	if (file_path)
	{
		return (file_path);
	}
	else
	{
		free(file_path);
		return (NULL);
	}
}
