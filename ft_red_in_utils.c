/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:37:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/11 21:42:42 by jsolinis         ###   ########.fr       */
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

void	ft_set_red_in(t_proc *proc, int i)
{
	proc->infile = 0;
	if ((*proc->lst)->infd)
		close((*proc->lst)->infd);
	(*proc->lst)->infd = open((*proc->lst)->args[i + 1], O_RDONLY);
	if ((*proc->lst)->infd < 0)
	{
		if (access((*proc->lst)->args[i + 1], F_OK) != 0)
			proc->infile = print_error(": No such file or directory", 1, (*proc->lst)->args[i + 1], 0);
		else
			printf("Error de acceso");
		(*proc->lst)->infd = 0;
	}
}

void	ft_set_red_in_del(t_proc *proc, int i)
{
	(*proc->lst)->infd = open("test", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (ft_strncmp((*proc->lst)->heredoc_line, (*proc->lst)->args[i + 1], ft_strlen((*proc->lst)->args[i + 1])) != 0)
	{
		(*proc->lst)->heredoc_line = readline("> ");
		if (ft_strncmp((*proc->lst)->heredoc_line, (*proc->lst)->args[i + 1], ft_strlen((*proc->lst)->args[i + 1])) != 0)
		{
			write((*proc->lst)->infd, (*proc->lst)->heredoc_line, ft_strlen((*proc->lst)->heredoc_line));
			write((*proc->lst)->infd, "\n", 1);
		}
	}
	if ((*proc->lst)->infd)
		close((*proc->lst)->infd);
	(*proc->lst)->infd = open("test", O_RDONLY);
	if ((*proc->lst)->infd < 0)
	{
		if (access("test", F_OK) != 0)
			proc->infile = print_error(": No such file or directory", 1, (*proc->lst)->args[i + 1], 0);
		else
			printf("Error de acceso");
		(*proc->lst)->infd = 0;
	}
	unlink("test");
}

