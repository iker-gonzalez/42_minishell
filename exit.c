/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:18:45 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv, int child, t_proc *proc)
{
	int	i;

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
		i = 0;
		if (argv[1][i] == '-' || argv[1][i] == '+')
			i++;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i++]))
				print_error(": numeric argument required", 255, argv[1], 1);
		}
		i = ft_atoi(argv[1]);
		ft_free(proc);
		exit ((i));
	}
}
