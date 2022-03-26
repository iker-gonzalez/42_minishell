/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:26:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/26 17:50:18 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

t_sig sig;

void	child_message(int signum)
{
	if (signum == SIGQUIT)
	{
		sig.status = 131;
		printf("Quit 3\n");
	}
	else if (signum == SIGINT)
	{
		sig.status = 130;
		printf("\n");
	}
}

void	handler(int signum)
{
	if (!sig.act_child)
	{
		if (signum == SIGINT)
		{
			sig.status = 1;
			printf("\n");
			rl_on_new_line();
			//rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		sig.status = 127;
		printf("%c", '\r');
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig.pid == 0)
	{
		sig.act_child = 0;
		exit(0);
	}
	child_message(signum);
}

void	listen_signals(void)
{
	//rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
