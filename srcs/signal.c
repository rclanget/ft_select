/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by rclanget          #+#    #+#             */
/*   Updated: 2017/01/06 16:54:27 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <signal.h>
#include <sys/ioctl.h>

#include "libft.h"

void			handle_winch(int i)
{
	get_size();
	if (i < 0 || GET(col) >= 100)
		print_elem(GET(list), 1, 0);
}

static void		handle_sigcont(int sig)
{
	char cp[1];

	cp[0] = GET(sauv).c_cc[VSUSP];
	if (sig == SIGCONT)
		ft_init();
	else
	{
		clear_win();
		stat_cursor(1);
		set_term(ft_glob(NULL)->sauv);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, cp);
	}
}

static void		handling_quit(int i)
{
	(void)i;
	clear_win();
	ft_exit();
}

void			handle_signal(void)
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
