#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_proc
{
	char	**process;
	char	**paths;
	char	*prompt;
	char	*line_read;
	int	cmd;
	int	quotation;
}		t_proc;

typedef struct s_iproc
{
	int	pid;
	int	fd[2];
	char	**tokens;
	char	*path;
	t_proc 	*proc;
}		t_iproc;

int	ft_find_next_quotation(char const *str, int i);
void	ft_format_paths(t_proc *proc);
void	ft_free_array(char **array);

#endif
