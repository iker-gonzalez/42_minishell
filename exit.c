/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 09:46:44 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_argc (char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return(i);
}

void	ft_exit(char **argv)
{
	int	i;
	int cmd_count;

	cmd_count = ft_count_argc(argv);
	if (cmd_count == 1)
		exit (0);
	if (cmd_count > 2)
		printf("Too many arguments.\n");
	if (cmd_count == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			if (!ft_isdigit(argv[1][i]))
				printf("Numeric argument required\n");
		}
		exit (ft_atoi(argv[1]));
	}
}