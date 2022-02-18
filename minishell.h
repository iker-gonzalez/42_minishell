#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

<<<<<<< HEAD
=======
typedef struct s_iproc
{
	int		pid;
	int		fd[2];
	char	**tokens;
	char	*path;
}			t_iproc;

>>>>>>> 6fdc0a008a65d2c80de142cbaf39b79e11b838bd
typedef struct s_proc
{
	char	**process;
	char	**paths;
	char	*prompt;
	char	*line_read;
<<<<<<< HEAD
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
=======
	int		cmd_count;
	int		cmd_found;
	int		quotation;
	t_iproc	*iproc;
}				t_proc;

void	set_up_shell(t_proc *proc);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, char *token, int processid);
void	ft_execute_command(t_proc *proc, char *route, int processid);
void	ft_tokenizer(char *process, t_proc *proc, int processid);
void	ft_read_input(t_proc *proc);

#endif
>>>>>>> 6fdc0a008a65d2c80de142cbaf39b79e11b838bd
