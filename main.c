/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:06 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:19:42 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_loop(t_set *set)
{
	t_proc	proc;
	int		ms_on;
	int		err;

	ms_on = 1;
	while (ms_on)
	{
		listen_signals_daddy();
		ft_memset(&proc, 0, sizeof(t_proc));
		proc.set = set;
		ft_create_terminal(&proc);
		err = ft_check_errors(&proc);
		if (!err)
		{
			ft_parse_input(&proc);
			ft_expand_input(&proc);
			ft_proceniser(&proc);
			ft_tokenizer(&proc);
			ft_launch_process(&proc);
			ft_free(&proc);
		}
		else
			free(proc.line_read);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_set	set;

	(void)argc;
	(void)argv;
	ft_memset(&set, 0, sizeof(t_set));
	set_up_shell(&set, env);
	ft_format_safe_paths(&set);
	ft_loop(&set);
	return (0);
}
