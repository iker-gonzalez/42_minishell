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

	t_iproc iproc;

	iproc.proc = proc;
	iproc.tokens = ft_split(process, ' ');
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

void	ft_get_paths(char *path, t_iproc *iproc)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	//paths[ft_get_nbr_words(path, ':')] = NULL;
	//free(path);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		path = ft_strjoin(paths[i], iproc->tokens[0]);
		free(paths[i]);
		paths[i] = path;
		if (access(paths[i], F_OK) == 0)
			iproc->path = paths[i];
		i++;
	}
}

int ft_execute(t_iproc *iproc)
{
	char *path;
	//ft_builtins();
	iproc = NULL;
	path = getenv("PATH");
	ft_get_paths(path, iproc);
	printf("%s\n", iproc->path);
	return (0);
}

int	ft_loop(t_proc *proc, t_iproc *iproc)
{
	int i;

	while (1)
	{
		ft_read_input(proc);
		ft_execute(iproc);
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
