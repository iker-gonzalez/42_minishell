/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:33:38 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/09 10:37:44 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void    ft_red_spc(t_proc *proc)
{
    int i;

    proc->red_spc = malloc(sizeof(int *) * (proc->added_spc));
    i = 0;
	printf("added spac: %d\n", proc->added_spc);
    while (i < proc->added_spc)
    {
        proc->red_spc[i] = malloc(sizeof(int));
        i++;
    }
}

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
	{
		if (arg[j] == '>')
				break ;
		else
			ret[i++] = arg[j];
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_outfile_red_next(char *arg)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc (ft_strlen(arg) + 1);
	while (arg[j])
	{
		if (arg[j] == '>')
				break ;
		else
			ret[i++] = arg[j++];
	}
	ret[i] = '\0';
	return (ret);
}

void	ft_set_red_out(t_proc *proc, int i, int j)
{
	char	*arg;

 	if ((*proc->lst)->args[i][j + 1])
	{
		arg = ft_outfile_red((*proc->lst)->args[i], j);		
	}
	else
	{
		arg = ft_outfile_red_next((*proc->lst)->args[i + 1]);
	}
	if ((*proc->lst)->outfd)
		close((*proc->lst)->outfd);
	(*proc->lst)->outfd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if ((*proc->lst)->outfd < 0)
		printf("Error al crear el fd para outfile");
}
