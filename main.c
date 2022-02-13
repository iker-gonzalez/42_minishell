#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	set_up_shell(t_proc *proc)
{
	char	*user;
	char	*logo;

	user = getenv("USER");
	logo = "papa$hell 🐚";
	proc->prompt = ft_strjoin(user, logo);
	ft_format_paths(proc);
}

void	ft_format_paths(t_proc *proc)
{
	char	*path;
	char	**paths;
	int	i;

	i = 0;
	path = getenv("PATH");
	paths = ft_split(path, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		proc->paths[i] = paths[i]; 
		i++;
	}
}

void	ft_tokenizer(char *process, t_proc *proc, t_iproc *iproc)
{
	iproc->proc = proc;
	iproc->tokens = ft_split(process, ' ');
}

void	ft_read_input(t_proc *proc, t_iproc *iproc)
{
	int	i;

	proc->line_read = readline(proc->prompt);
	add_history(proc->line_read);
	i = 0;
	proc->cmd = 1;
	while (proc->line_read[i])
	{
		//i += ft_find_next_quotation(proc->line_read, i);
		if (proc->line_read[i] == '|')
			proc->cmd++;
		i++;
	}
	if (proc->cmd > 1)
	{
		proc->process = ft_split(proc->line_read, '|');
		i = 0;
		while(proc->process[i])
		{
			ft_tokenizer(proc->process[i], proc, iproc);
			i++;
		}
	}
	else
		ft_tokenizer(proc->line_read, proc, iproc);
}

void ft_find_path(t_proc *proc, t_iproc *iproc)
{
	int	i;

	i = 0;
	while (iproc->tokens[i])
	{
		printf("TOKEN %d: %s\n", i, iproc->tokens[i]);
		i++;
	}
	i = 0;
	while(proc->paths[i])
	{
		printf("PATH %d: %s\n", i, proc->paths[i]);
		i++;
	}
}

int ft_execute(t_proc *proc, t_iproc *iproc)
{
	//ft_builtins();
	ft_find_path(proc, iproc);
	return (0);
}

int	ft_loop(t_proc *proc, t_iproc *iproc)
{
	int i;

	while (1)
	{
		ft_read_input(proc, iproc);
		ft_execute(proc, iproc);
		i = 0;
	}
	return(0);
}
/*
void ft_execute_command(void)
{
	char *cmd;
	char *str;
	char **arg;
	char *env;
	
	cmd = "/bin/ls";
	str = "ls -l";
	arg = ft_split(str, ' ');
	env = NULL;
	execve(cmd, arg, &env);
}
*/
int main (void)
{
	t_proc proc;
	t_iproc iproc;

	//ft_execute_command();
	set_up_shell(&proc);
	ft_loop(&proc, &iproc);
	return(0);
}
