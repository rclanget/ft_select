/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/23 20:04:38 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <signal.h>

void	handle_sigcont(int sig)
{
	if (sig == SIGCONT)
		ft_init();
	else
	{
		set_term(ft_glob(NULL)->sauv);
		signal(SIGTSTP, SIG_DFL);
		// ioctl(0, TIOCSTI, "\032");
	}
}

void		handle_winch(int i)
{
	(void)i;
	get_size();
	print_elem(ft_glob(NULL)->list);
}

void		handling_quit(int i)
{
	set_term(ft_glob(NULL)->sauv);
	ft_exit();
}

int			handle_signal(void)
{
	int i;

	i = 0;
	while (++i < 32)
	{
		if (i == SIGCONT || i == SIGTSTP)
			signal(i, hangle_sigcont);
		else if (i == SIGWINCH)
			signal(i, handle_winch);
		else if (i != SIGURG && i != SIGCHLD && i != SIGTTIN
			&& i != SIGTTOU && i != SIGIO)
			signal(i, handling_quit);
	}
}