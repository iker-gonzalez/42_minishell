#include "minishell.h"

char *ft_strcat(char *dst, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return(dst);
}

void	set_up_shell(t_proc *proc)
{
	char *user;
	char *logo;
	size_t	length;

	user = getenv("USER");
	logo = "\033[38;2;243;134;48mpapa$hell 🐚\033[0m";
	length = ft_strlen(user) + ft_strlen(logo) + 1;
	proc->prompt = malloc(sizeof (char) * length + 1);
	proc->prompt = ft_strcat(ft_strcat(ft_strcat(proc->prompt, user),"@"),logo);
}

void	ft_tokenizer(char *process, t_proc *proc)
{
	int	i;

	i = 0;
	proc->tokens = ft_split(process, ' ');
}

void	ft_read_input(t_proc *proc)
{
	int	i;

	proc->line_read = readline(proc->prompt);
	add_history(proc->line_read);
	i = 0;
	//ft_memset(proc, 0, sizeof(t_proc));
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
			ft_tokenizer(proc->process[i], proc);
			i++;
		}
	}
	else
		ft_tokenizer(proc->line_read, proc);
}

int	ft_loop(t_proc *proc)
{
	int i;

	while (1)
	{
		ft_read_input(proc);
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

	//ft_execute_command();
	set_up_shell(&proc);
	ft_loop(&proc);
	return(0);
}
