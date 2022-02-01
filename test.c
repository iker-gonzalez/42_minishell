#include "minishell.h"

int main (void)
{
	char *str;

	while (1)
	{
		str = readline("\033[38;2;243;134;48m$papashell 🐚\033[0m ");
		free (str);
	}
}
