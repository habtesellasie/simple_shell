#include "main.h"

/**
 * handle_signal_2 - the function that handles SIGNINT
 * @itr: integer
 * Return: void
 */
void handle_signal_2(int itr)
{
	(void) itr;
	write(STDOUT_FILENO, "\n$ ", 3);
}
