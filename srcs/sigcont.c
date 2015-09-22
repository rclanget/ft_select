/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcont.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:32 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 16:00:59 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

#include <signal.h>

void	get_continue(int i)
{
	char			*name_term;
	struct termios	term;

	(void)i;
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	tgetent(NULL, name_term);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	get_canon(term);
	get_new_size();
}


void	handle_sigcont(void)
{
	signal(SIGCONT, get_continue);
}