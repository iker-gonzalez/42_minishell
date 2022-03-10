#include "minishell.h"
#include <stdlib.h>

void	ft_free_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i++])
		free(str[i]);
	free(str);
}


void	ft_free_proc(t_proc *proc)
{
	ft_free_double_char(proc->tokens);
	//ft_free_double_char(proc->line_expanded);	
}
