/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:06 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/01 10:54:55 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_loop(t_set *set)
{
	t_proc	proc;
	int	ms_on;

	ms_on = 1;
	while (ms_on)
	{
		ft_memset(&proc, 0, sizeof(t_proc));
		proc.set = set;
		ft_create_terminal(&proc);
		if (ft_check_errors(&proc) == 0)
		{
			ft_parse_input(&proc);
			ft_expand_input(&proc);
			ft_tokenizer(&proc);
			ft_launch_process(&proc);
		}
		ft_free(&proc);
		//ft_print_val(proc);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_set	set;
	(void)argc;
	(void)argv;
	listen_signals();
	ft_memset(&set, 0, sizeof(t_set));
	set_up_shell(&set, env);
	ft_loop(&set);
	return (0);
}
