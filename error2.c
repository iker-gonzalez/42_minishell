/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:10:13 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/02 10:19:29 by ikgonzal         ###   ########.fr       */
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
			ft_putendl_fd("syntax error near unexpected token `>'", 2);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}

int	ft_check_redirections(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			if (ft_check_3redirections(line, c, &i))
				return (1);
			while (line[i] && line[i] == 32)
				i++;
			if (line[i] == '\0' || line[i] == 60
				|| line[i] == 62 || line[i] == 124)
			{
				ft_putstr_fd("papa$hell: ", 2);
				ft_putendl_fd
				("syntax error near unexpected token `newline'", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_check_null_line(char *line_read)
{
	if (line_read == NULL)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

