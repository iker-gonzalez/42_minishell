/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:41:05 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/24 08:25:37 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_3redirections(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			ft_putstr_fd("papa$hell: ", 2);
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}

int ft_check_redirections(char *line, char c)
{
    int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			if (ft_check_3redirections(line, c, &i))
				return (1);
			while (line[i] && line[i] == 32)
				i++;
			if (line[i] == '\0' || line[i] == 60 || line[i] == 62|| line[i] == 124)
			{
				ft_putstr_fd("papa$hell: ", 2);
				ft_putendl_fd("syntax error near unexpected token `newline'", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int ft_check_unclosed_quotes(char *line_read, char c)
{
    int i;
    int ret;

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

int ft_check_empty_line(char *line_read)
{
    char *line;
    
    line = ft_strtrim(line_read, " ");
    if (line_read[0] == '\0')
    {
        free(line);
        return(1);
    }
    free (line);
    return(0);
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

void    ft_check_errors(t_proc *proc)
{
    if (ft_check_empty_line(proc->line_read))
        printf("Empty line\n");
    if (ft_check_empty_pipe(proc->line_read))
        exit (2);
    if (ft_check_unclosed_quotes(proc->line_read, 34))
        exit (2);
    if (ft_check_unclosed_quotes(proc->line_read, 39))
        exit (2);
	if (ft_check_redirections(proc->line_read, 60))
		exit (2);
	if (ft_check_redirections(proc->line_read, 62))
		exit (2);
}