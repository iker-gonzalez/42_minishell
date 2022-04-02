/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out_app_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:01:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/02 22:58:00 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

char	*ft_outfile_app_red(char *arg, int j)
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

void	ft_set_red_out_app(t_proc *proc, int i, int j)
{
	char	*arg;

 	if ((*proc->lst)->args[i][j + 2])
		arg = ft_outfile_app_red((*proc->lst)->args[i], j);
	else
		arg = (*proc->lst)->args[i + 1];
	if ((*proc->lst)->outfd)
		close((*proc->lst)->outfd);
	(*proc->lst)->outfd = open(arg, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if ((*proc->lst)->outfd < 0)
		printf("Error al crear el fd para outfile");
}
