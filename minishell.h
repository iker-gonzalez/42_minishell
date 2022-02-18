#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_iproc
{
	int		pid;
	int		fd[2];
	char	**tokens;
	char	*path;
}			t_iproc;

typedef struct s_proc
{
	char	**process;
	char	**paths;
	char	*prompt;
	char	*line_read;
	int		cmd_count;
	int		cmd_found;
	int		*quoted;
	int		sinqle_quotes;
	int		double_quotes;
	t_iproc	*iproc;
}				t_proc;

void	set_up_shell(t_proc *proc);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, char *token, int processid);
void	ft_execute_command(t_proc *proc, char *route, int processid);
void	ft_tokenizer(char *process, t_proc *proc, int processid);
void	ft_read_input(t_proc *proc);

#endif
