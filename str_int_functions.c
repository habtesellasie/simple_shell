#include "main.h"

/**
 * convert_to_str - convert an integer to a string
 * @num: the integer number
 * Return: the string containing the num
 */
char *convert_to_str(int num)
{
	int digit, i = 0;
	char *str = malloc(sizeof(char) * 10);

	if (!str)
		return (NULL);

	while (num)
	{
		digit = num % 10;
		str[i++] = '0' + digit;
		num /= 10;
	}
	rev_str(str, i);
	str[i] = '\0';
	return (str);
}

/**
 * rev_str - reversing a string
 * @str: to reverse a string
 * @i: the length of a string
 * Return: void
 */
void rev_str(char *str, int i)
{
	int loop = i - 1;
	int loot = 0;
	char temp;

	for (; loot < loop; loot++, loop--)
	{
		temp = str[loot];
		str[loot] = str[loop];
		str[loop] = temp;
	}
}

/**
 * convert_to_int - convert a strings to an integer
 * @str: convert string
 * Return: Converted integer
 */
int convert_to_int(char *str)
{
	int no, i, mlkt;

	no = i = mlkt = 0;

	if (str[i] == '-')
	{
		mlkt = 1;
		i++;
	}

	while (str[i])
	{
		no = (no * 10) + (str[i] - '0');
		i++;
	}

	if (mlkt)
		no *= -1;

	return (no);
}
