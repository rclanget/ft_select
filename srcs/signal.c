/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by rclanget          #+#    #+#             */
/*   Updated: 2016/12/31 16:53:55 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <signal.h>
#include <sys/ioctl.h>

void		handle_sigcont(int sig)
{
	char cp[1];

	cp[0] = GET(sauv).c_cc[VSUSP];
	if (sig == SIGCONT)
		ft_init();
	else
	{
		set_term(ft_glob(NULL)->sauv);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, cp);
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
