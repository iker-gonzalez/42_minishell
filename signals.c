/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:26:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/05 11:56:21 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>


void	child_message(int signum)
{
	if (signum == SIGQUIT)
	{
		g_sig.status = 131;
		printf("Quit 3\n");
		g_sig.act_child = 0;
	}
	else if (signum == SIGINT)
	{
		g_sig.status = 130;
		printf("\n");
		g_sig.act_child = 0;
	}
}

void	handler(int signum)
{
	if (!g_sig.act_child)
	{
		if (signum == SIGINT)
		{
			g_sig.status = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		return ;
	}
	if (g_sig.pid == 0)
	{
		printf("pid: %d\n", g_sig.pid);
		printf("child\n");
		g_sig.act_child = 0;
	}
	child_message(signum);
}

void	listen_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
