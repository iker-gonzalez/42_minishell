#include "minishell.h"

int	ft_loop(t_proc *proc)
{

	while (1)
	{
		ft_read_input(proc);
		ft_parse_input(proc);
	}
	return(0);
}

int main (void)
{
	t_proc proc;

	ft_memset(&proc, 0, sizeof(t_proc));
	set_up_shell(&proc);
	ft_loop(&proc);
	return(0);
}
