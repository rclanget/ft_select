/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/29 16:45:47 by ulefebvr         ###   ########.fr       */
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
	print_elem(GET(list), 1, 0);

	// if (i)
	// 	clear_win();
	// SET(col, (GET(col) / (GET(maxlen))) - 1);
	// SET(line, ((GET(list->prev->no) + 1) / GET(col)));
	// ft_printf("col %d line %d\n", GET(col), GET(line));
	// print_list();
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