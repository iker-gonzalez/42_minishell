#include "minishell.h"

int ft_find_next_quotation(char *str, int i)
{
	printf("i: %d\n", i);
	printf("%c\n", str[i]);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	printf("i: %d\n", i);
	return i;
}

int main (void)
{
	t_utils utils;
	int i;
	char *str;
	char **commands;
	char *command;

	while (1)
	{
		str = readline("\033[38;2;243;134;48mpapa$hell 🐚\033[0m");
		add_history(str);
		i = 0;
		utils.lock = 0;
		while (str[i])
		{
			if (str[i] == 34 || str[i] == 39)
			{
				printf("I: %d\n", i);
				i = ft_find_next_quotation(str, i + 1);
				printf("I: %d\n", i);
			}
			if (str[i] == '|')
			{
				printf("SPLIT\n");
				commands = ft_split(str, '|');
				printf("multiple commands[0]: %s\n", commands[0]);
				utils.lock = 1;
				break ;
			}
			i++;
		}
		if (!utils.lock)
		{
			command = str;
			printf("single command: %s\n", command);
		}
		//free (str);
	}
}
