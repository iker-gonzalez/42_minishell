/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:41:05 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/10 21:20:01 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	ft_check_unclosed_quotes(char *line_read, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (line_read[i])
	{
		if (line_read[i] == c)
		{
			if (!ret)
				ret = 1;
			else
				ret = 0;
		}
		i++;
	}
	if (ret)
	{
		ft_putstr_fd("papa$hell:", 2);
		ft_putstr_fd(" Syntax error, unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_empty_line(char *line_read)
{
	char	*line;

	line = ft_strtrim(line_read, " ");
	if (line_read[0] == '\0')
	{
		free(line);
		return (1);
	}
	free (line);
	return (0);
}

int	ft_check_empty_pipe(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] && line_read[i] == ' ')
		i++;
	if (line_read[i] == '|')
	{
		ft_putstr_fd("papa$hell:", 2);
		ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	i = -1;
	while (line_read[++i])
	{
		if (line_read[i] == '|' && line_read[i + 1] == '\0')
		{
			ft_putstr_fd("papa$hell:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_check_errors(t_proc *proc)
{
	if (ft_check_null_line(proc->line_read))
		exit (0);
	if (ft_check_empty_line(proc->line_read))
		return (127);
	if (ft_check_empty_pipe(proc->line_read))
		return (258);
	if (ft_check_unclosed_quotes(proc->line_read, 34))
		return (1);
	if (ft_check_unclosed_quotes(proc->line_read, 39))
		return (1);
	if (ft_check_redirections(proc->line_read, 60))
		return (258);
	if (ft_check_redirections(proc->line_read, 62))
		return (258);
	return (0);
}

int	print_error(char *str, int err, char *cmd, int child)
{
	ft_putstr_fd("Papa$hell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	g_sig.exit_status = err;
	if (child)
		exit(err);
	else
		return(err);
}
