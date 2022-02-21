#include "minishell.h"
/*
void	ft_tokenizer(char *process, t_proc *proc, int processid)
{
	t_iproc iproc;
	int		i;

	proc->iproc = &iproc;
	proc->iproc->tokens = ft_split(process, ' ');
	i = 0;
	while (proc->iproc->tokens[i])
	{
		ft_cmd_exist(proc, proc->iproc->tokens[i], processid);
		i++;
	}
}
*/
void	ft_read_input(t_proc *proc)
{
	proc->line_read = readline(proc->prompt);
	add_history(proc->line_read);
}	
