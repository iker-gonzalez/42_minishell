#include "minishell.h"
/*
void ft_execute_command(t_proc *proc, char *route, int processid)
{
	char **arg;
	char *env;
	
	if (proc->cmd_count > 1)
		arg = ft_split(proc->process[processid], ' ');
	else
		arg = ft_split(proc->line_read, ' ');
	env = NULL;
	execve(route, arg, &env);
}

void	ft_cmd_exist(t_proc *proc, char *token, int processid)
{
	int		i;

	i = 0;
	proc->cmd_found = 0;
	while (proc->paths[i])
	{
		proc->paths[i] = ft_strjoin(proc->paths[i], token);
		if (access(proc->paths[i], F_OK) == 0)
		{
			proc->cmd_found = 1;
			ft_execute_command(proc, proc->paths[i], processid);
		}
		i++;
	}
}
*/