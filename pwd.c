/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:25:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 20:18:27 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	ft_pwd(int child, int fd)
{
	size_t	cnt;
	char	str[PATH_MAX];

	fd = 1;
	if (getcwd(str, PATH_MAX) == NULL)
		return (1);
	cnt = ft_strlen(str);
	write(fd, str, cnt);
	write(fd, "\n", 1);
	if (child)
		exit (0);
	return (0);
}
