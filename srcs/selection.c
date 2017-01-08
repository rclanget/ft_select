/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:26 by rclanget          #+#    #+#             */
/*   Updated: 2017/01/08 17:46:45 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

#define UP_KEY		4283163
#define DOWN_KEY	4348699
#define LEFT_KEY	4479771
#define RIGHT_KEY	4414235
#define ENTER_KEY	10
#define ESC_KEY		27
#define SPACE_KEY	32
#define DEL_KEY		127

#define IS_IN_RANGE(x, min, max)	((x) >= (min) && (x) <= (max))

static int		get_move(int no, int move)
{
	int		last;
	int		line;

	last = GET(list)->prev->no;
	line = GET(line);
	if (IS_IN_RANGE(move, -1, 1) || ((move + no) <= last && move > 0))
		return (no + move);
	else if (move < 0 && (no + move >= 0))
		return (no + move);
	else if (move > 0)
		return (no - (move * (no / move)));
	no += ((last / line) * line);
	while (no > last && no >= 0)
		no -= line;
	return (no);
}

static t_lst	*get_elemno(int move, int no)
{
	t_lst	*begin;
	int		last;

	begin = ft_glob(NULL)->list;
	last = ft_glob(NULL)->list->prev->no;
	if (no < 0 || no > last)
		no = (no < 0) ? last : 0;
	while (begin->no != no)
		begin = begin->next;
	while (begin->dlted)
		begin = (move > 0) ? begin->next : begin->prev;
	return (begin);
}

static void		selection(int move, int del)
{
	t_lst	*begin;

	begin = ft_glob(NULL)->list;
	while (!begin->crrnt)
		begin = begin->next;
	begin->crrnt = 0;
	if (move)
		get_elemno(move, get_move(begin->no, move))->crrnt = 1;
	else
	{
		get_elemno(1, begin->no + 1)->crrnt = 1;
		begin->slctd = (!del && !begin->slctd) ? 1 : 0;
		begin->dlted = del;
	}
}

static void		enter(void)
{
	t_lst	*begin;
	int		selected;

	selected = 0;
	begin = ft_glob(NULL)->list;
	clear_win();
	while (1)
	{
		if (begin->slctd)
			ft_print((selected++) ? " %s" : "%s", begin->file);
		if ((begin = begin->next)->start)
			break ;
	}
	ft_print((selected) ? "\n" : "");
	ft_exit();
}

int				looping(void)
{
	int		c;

	while (1)
	{
		c = 0;
		read(0, &c, sizeof(int));
		if (c == UP_KEY || c == DOWN_KEY)
			selection(c == UP_KEY ? -1 : 1, 0);
		else if (c == DEL_KEY || c == SPACE_KEY)
			selection(0, c == DEL_KEY ? 1 : 0);
		else if (c == ENTER_KEY)
			enter();
		else if (c == ESC_KEY)
		{
			clear_win();
			ft_exit();
		}
		print_elem(ft_glob(NULL)->list, 1, 0);
	}
	return (0);
}
