/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 11:24:01 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv)
{
	int	i;
	int	cmd_count;

	cmd_count = ft_count_argc(argv);
	if (cmd_count == 1)
		exit (0);
	if (cmd_count > 2)
		print_error("Too many arguments.\n", 1);
	if (cmd_count == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			if (!ft_isdigit(argv[1][i]))
				print_error("Numeric argument required", 255);
		}
		exit (ft_atoi(argv[1]));
	}
}
