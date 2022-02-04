#include "minishell.h"

int ft_find_next_quotation(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	return i;
}

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

void	set_up_shell(t_process *processes)
{
	char *user;
	char *logo;
	size_t	length;

	user = getenv("USER");
	logo = "\033[38;2;243;134;48mpapa$hell 🐚\033[0m";
	length = ft_strlen(user) + ft_strlen(logo) + 1;
	processes->prompt = malloc(sizeof (char) * length + 1);
	processes->prompt = ft_strcat(ft_strcat(ft_strcat(processes->prompt, user),"@"),logo);
}

void	ft_parse_process(char *process, t_process *processes)
{


}

void	ft_read_input(t_process *processes)
{
	int	i;

	processes->line_read = readline(processes->prompt);
	add_history(processes->line_read);
	i = 0;
	ft_memset(&processes, 0, sizeof(t_process));
	processes->cmd = 1;
	while (processes->line_read[i])
	{
		if (processes->line_read[i] == '|')
			processes->cmd++;
		i++;
	}
	if (processes->cmd > 1)
	{
		processes->process = ft_split(processes->line_read, '|');
		i = 0;
		while(processes->process[i])
		{
			ft_parse_process(processes->process[i], processes);
			i++;
		}
	}
	else
		ft_parse_process(processes->line_read, processes);
}

int	ft_loop(t_process *processes)
{
	int i;

	while (1)
	{
		ft_read_input(processes->prompt);
		i = 0;
	}
	return(0);
}

int main (int argc, char **envp)
{
	t_process processes;

	/*execve("usr/bin/wc", arg, envp);
	char *str = "wc file.txt";
	char **arg = ft_split(str, ' ');
	argc = access("/usr/bin/wc", F_OK);
	printf("%d", argc);*/
	set_up_shell(&processes);
	ft_loop(&processes);
	return(0);
}
