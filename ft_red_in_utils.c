/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:37:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/04 20:23:00 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void	ft_set_red_read(int fd)
{
	dup2(fd, 0);
	close(fd);
}

char	*ft_infile_red(char *arg, int j)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc (ft_strlen(arg) - j);
	while (arg[++j])
		ret[i++] = arg[j];
	ret[i] = '\0';
	printf("%s\n", ret);
	return (ret);
}

void	ft_set_red_in(t_proc *proc, int i, int j)
{
	char	*arg;

 	if ((*proc->lst)->args[i][j + 1])
		arg = ft_infile_red((*proc->lst)->args[i], j);
	else
		arg = (*proc->lst)->args[i + 1];
	if ((*proc->lst)->infd)
		close((*proc->lst)->infd);
	(*proc->lst)->infd = open(arg, O_RDONLY);
	if ((*proc->lst)->infd < 0)
	{
		if (access(arg, F_OK) != 0)
			printf("Archivo no existe");
		else
			printf("Error de acceso");
	}
}
