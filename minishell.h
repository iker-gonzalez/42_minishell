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


typedef struct s_process
{
	char			**process;
	char			*prompt;
	char			*line_read;
	int				cmd;
	t_ind_process *ind_process;

}				t_process;


#endif