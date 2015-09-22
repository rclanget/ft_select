/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 14:00:34 by ulefebvr         ###   ########.fr       */
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

void	selection(int move)
{
	t_lst	*begin;

	begin = ft_glob(NULL)->list;
	while (!begin->crrnt)
		begin = begin->next;
	begin->crrnt = 0;
	get_elemno(begin->no + move)->crrnt = 1;
}

int		looping(void)
{
	char	buf[3];

	read(0, buf, 3);
	if (buf[0] == 27)
	{
		if (buf[2] == 'A')
			selection(-1);
		if (buf[2] == 'B')
			selection(1);
		print_elem(ft_glob(NULL));
	}
	return (0);
}