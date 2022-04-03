/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:56 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/03 18:19:15 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <string.h>

int	ft_echo(char **argv, int fd)
{
	int		i;
	size_t	cnt;

	if (!fd)
		fd = 1;
	i = 1;
	if (strcmp(argv[i], "-n") == 0)
		i++;
	while (argv[i])
	{
		cnt = ft_strlen(argv[i]);
		write(fd, argv[i], cnt);
		if (argv)
			write(fd, " ", 1);
		i++;
	}
	if (fd != 1)
		write(fd, "\n", 1);
	if (fd == 1 && (strcmp(argv[1], "-n") != 0))
		write(fd, "\n", 1);
	return (0);
}
