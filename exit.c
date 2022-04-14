/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 19:41:33 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv, int child, t_set *set, t_proc *proc)
{
	int	i;
	int	cmd_count;

	ft_free_double_char(set->env);
	cmd_count = ft_count_argc(argv);
	if (!child)
		printf("exit\n");
	if (cmd_count == 1)
	{
		ft_free(proc);
		exit (0);
	}
	if (cmd_count > 2)
		print_error(": too many arguments.", 1, argv[1], 1);
	if (cmd_count == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			if (!ft_isdigit(argv[1][i]))
				print_error(": numeric argument required", 255, argv[1], 1);
		}
		ft_free(proc);
		exit (ft_atoi(argv[1]));
	}
}
