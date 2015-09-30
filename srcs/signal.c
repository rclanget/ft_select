/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 12:25:33 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <signal.h>

void		handle_sigcont(int sig)
{
	if (sig == SIGCONT)
		ft_init();
	else
	{
		set_term(ft_glob(NULL)->sauv);
		signal(SIGTSTP, SIG_DFL);
	}
}

void		handle_winch(int i)
{
	(void)i;
	get_size();
	print_elem(GET(list), 1, 0);
}

void		handling_quit(int i)
{
	(void)i;
	set_term(ft_glob(NULL)->sauv);
	ft_exit();
}

void		handle_signal(void)
{
	int i;

	i = 0;
	while (++i < 32)
	{
		if (i == SIGCONT || i == SIGTSTP)
			signal(i, handle_sigcont);
		else if (i == SIGWINCH)
			signal(i, handle_winch);
		else if (i != SIGURG && i != SIGCHLD && i != SIGTTIN
			&& i != SIGTTOU && i != SIGIO)
			signal(i, handling_quit);
	}
}
