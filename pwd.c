/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:25:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 11:57:49 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	ft_pwd(void)
{
	char	str[PATH_MAX];

	if (getcwd(str, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", str);
	return (0);
}
