/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:40:39 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/25 12:59:56 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	ft_pwd(void)
{
	char str[PATH_MAX];

	if (getcwd(str, PATH_MAX) == NULL)
		return(1);
	printf("%s\n", str);
	return(0);
}
