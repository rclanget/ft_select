/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 14:26:38 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_lst	*get_elemno(int no)
{
	t_lst	*begin;
	int		last;

	begin = ft_glob(NULL)->list;
	last = ft_glob(NULL)->list->prev->no;
	if (no < 0 || no > last)
		return (no < 0 ? begin->prev : begin);
	while (begin->no != no)
		begin = begin->next;
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
		get_elemno(begin->no + move)->crrnt = 1;
	else if (!sel)
	{
		begin->next->crrnt = 1;
		if (!del)
			begin->slctd = 1;
		else
			begin->dlted = 1;
	}
}

int		looping(void)
{
	char	buf[3];

	read(0, buf, 3);
	if (buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 'A')
			selection(-1, 0);
		if (buf[2] == 'B')
			selection(1, 0);
	}
	else if (buf[0] == 32 && buf[1] == 91 && buf[2] == 68)
		selection(0, 1);
	else if (buf[0] == 32 && buf[1] == 0 && buf[2] == 0)
		selection(0, 0);
	print_elem(ft_glob(NULL));
	return (0);
}