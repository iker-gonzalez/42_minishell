/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:56 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:49:58 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_write_arg(int fd, char **argv)
{
	size_t	cnt;
	int		i;

	i = 1;
	if (ft_strncmp_len(argv[i], "-n", 2) == 0)
		i++;
	while (ft_strncmp_len(argv[i], "-n", 2) == 0)
		i++;
	while (argv[i])
	{
		cnt = ft_strlen(argv[i]);
		write(fd, argv[i], cnt);
		if (argv[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

int	ft_echo(t_proc *proc, char **argv, int fd, int child)
{
	if (proc->process_count != 1)
		fd = 1;
	if (!argv[1])
	{
		write(fd, "\n", 1);
		if (child)
			exit(0);
		return (0);
	}
	ft_write_arg(fd, argv);
	if (ft_strncmp_len(argv[1], "-n", 2) != 0)
		write(fd, "\n", 1);
	if (child)
		exit (0);
	return (0);
}
