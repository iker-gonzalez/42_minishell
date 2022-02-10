#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_ind_process
{
	int	pid;
	int	fd[2];

}				t_ind_process;


typedef struct s_proc
{
	char			**process;
	char			**tokens;
	char			*prompt;
	char			*line_read;
	int				cmd;
	int				quotation;

	//t_ind_process *ind_process;

}				t_proc;

int ft_find_next_quotation(char const *str, int i);


#endif