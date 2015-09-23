/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/23 17:19:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include "ft_printf.h"

#define UP_KEY		4283163
#define DOWN_KEY	4348699
#define LEFT_KEY	4479771
#define RIGHT_KEY	4414235
#define ENTER_KEY	10
#define ESC_KEY		27
#define SPACE_KEY	32
#define DEL_KEY		127

t_lst	*get_elemno(int move, int no)
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

void	selection(int move, int del)
{
	t_lst	*begin;

	begin = ft_glob(NULL)->list;
	while (!begin->crrnt)
		begin = begin->next;
	begin->crrnt = 0;
	if (move)
		get_elemno(move, begin->no + move)->crrnt = 1;
	else
	{
		get_elemno(1, begin->no + 1)->crrnt = 1;
		begin->slctd = (!del && !begin->slctd) ? 1 : 0;
		begin->dlted = del;
	}
}

void	enter(void)
{
	t_lst	*begin;
	int		selected;

	selected = 0;
	begin = ft_glob(NULL)->list;
	clear_win();
	while (1)
	{
		if (begin->slctd)
			ft_printf((selected++) ? " %s" : "%s", begin->file);
		if ((begin = begin->next)->start)
			break ;
	}
	ft_printf((selected) ? "\n" : "");
	ft_exit();
}

void	escape_select(void)
{
	clear_win();
	ft_exit();
}

int		looping(void)
{
	int		c;

	while (1)
	{
		c = 0;
		read(0, &c, sizeof(int));
		if (c == UP_KEY)
			selection(-1, 0);
		else if (c == DOWN_KEY)
			selection(1, 0);
		else if (c == DEL_KEY)
			selection(0, 1);
		else if (c == SPACE_KEY)
			selection(0, 0);
		else if (c == ENTER_KEY)
			enter();
		else if (c == ESC_KEY)
			escape_select();
		print_elem(ft_glob(NULL)->list);
	}
	return (0);
}