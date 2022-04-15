/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 18:35:10 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv, int child, t_set *set, t_proc *proc)
{
	int	i;

	ft_free_double_char(set->env);
	if (!child)
		printf("exit\n");
	if ((ft_count_argc(argv)) == 1)
	{
		ft_free(proc);
		exit (0);
	}
	if (ft_count_argc(argv) > 2)
		print_error(": too many arguments.", 1, argv[1], 1);
	if ((ft_count_argc(argv)) == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			if (!ft_isdigit(argv[1][i]))
				print_error(": numeric argument required", 255, argv[1], 1);
		}
		i = ft_atoi(argv[1]);
		ft_free(proc);
		exit ((i));
	}
}
