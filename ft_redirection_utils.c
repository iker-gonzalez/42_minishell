/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:54:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/02 16:47:40 by ikgonzal         ###   ########.fr       */
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

void	ft_check_red_type(t_proc *proc)
{
	int	i;
	int	j;
	char *arg;

	i = 0;
	proc->red_out_arr_len = 0;
	while ((*proc->lst)->args[i])
	{
		j = 0;
		while ((*proc->lst)->args[i][j])
		{
			if ((*proc->lst)->args[i][j] == 62 && proc->red_out_arr[proc->red_out_arr_len++] == 1)
			{
			   	if ((*proc->lst)->args[i][j + 1])
					arg = ft_outfile_red((*proc->lst)->args[i], j);
				else
					arg = (*proc->lst)->args[i + 1];
				if ((*proc->lst)->outfd)
					close((*proc->lst)->outfd);
				(*proc->lst)->outfd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if ((*proc->lst)->outfd < 0)
					printf("Error al crear el fd para outfile");	
			}
			j++;
		}
		i++;
	}
}
