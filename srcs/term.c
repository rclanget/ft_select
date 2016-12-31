/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 15:30:41 by rclanget          #+#    #+#             */
/*   Updated: 2015/10/13 15:33:26 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <sys/ioctl.h>

void	set_term(struct termios term)
{
	tcsetattr(0, TCSADRAIN, &term);
}

void	get_canon(struct termios term)
{
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	set_term(term);
}

void	clear_win(void)
{
	int	line;

	line = GET(line);
	while (line-- >= 0)
	{
		PUT("dl");
		put_cursor(line, 0);
	}
}

void	stat_cursor(int stat)
{
	PUT(stat ? "ve" : "vi");
}

void	get_size(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	SET(col, w.ws_col);
	SET(line, w.ws_row);
}
