#include "minishell.h"

void	count_quotations(t_proc *proc)
{
	int i;

	i = 0;
	proc->squote_count = 0;
	proc->dquote_count = 0;
	while(proc->line_read[i])
	{
		if(proc->line_read[i] == 34)
			proc->dquote_count++;
		else if (proc->line_read[i] == 39)
			proc->squote_count++;
		i++;
	}
	printf("single: %d\n", proc->squote_count);
	printf("double: %d\n", proc->dquote_count);
}

void	ft_read_input(t_proc *proc)
{
	proc->line_read = readline(proc->prompt);
	add_history(proc->line_read);
	count_quotations(proc);
}	
