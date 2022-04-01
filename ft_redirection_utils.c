/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:54:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/02 00:55:22 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void	ft_set_red_write(int fd)
{
	dup2(fd, 1);
	close(fd);
}

char	*ft_outfile_red(char *arg, int j)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc (ft_strlen(arg) - j);
	while (arg[++j])
		ret[i++] = arg[j];
	ret[i] = '\0';
	return (ret);
}

void	ft_check_red_type(t_node *node)
{
	int	i;
	int	j;
	char *arg;

	i = 0;
	while (node->args[i])
	{
		j = 0;
		while (node->args[i][j])
		{
			if (node->args[i][j] == 62)
			{
			   	if (node->args[i][j + 1])
					arg = ft_outfile_red(node->args[i], j);
				else
					arg = node->args[i + 1];
				if (node->outfd)
					close(node->outfd);
				node->outfd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if (node->outfd < 0)
					printf("Error al crear el fd para outfile");	
			}
			j++;
		}
		i++;
	}
}
