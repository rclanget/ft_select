/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/23 10:43:23 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

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
	int		last;

	last = ft_glob(NULL)->list->prev->no;
	begin = ft_glob(NULL)->list;
	while (begin)
	{
		if (begin->slctd)
		{
			ft_fdprintf("%s", begin->file);
			if (begin->no < last)
				ft_fdprintf(ft_glob(NULL)->out_fd, " ");
		}
		if ((begin = begin->next)->start)
		{
			ft_fdprintf(ft_glob(NULL)->out_fd, "\n");
			break ;
		}
	}
	ft_exit();
}

int		looping(void)
{
	char	buf[3];

	ft_bzero(buf, 3);
	read(0, buf, 3);
	if (buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 'A')
			selection(-1, 0);
		if (buf[2] == 'B')
			selection(1, 0);
	}
	else if (buf[0] == 127 && buf[1] == 0 && buf[2] == 0) // del
		selection(0, 1);
	else if (buf[0] == 32 && buf[1] == 0 && buf[2] == 0) // espace
		selection(0, 0);
	else if (buf[0] == 10 && buf[1] == 0 && buf[2] == 0)
		enter();
	print_elem(ft_glob(NULL)->list);
	return (0);
}