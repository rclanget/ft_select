/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 14:49:48 by rclanget          #+#    #+#             */
/*   Updated: 2016/12/31 18:06:03 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

#include <stdlib.h>

static t_lst	*create_list(char **argv, int start, t_lst *prev, int number)
{
	t_lst		*elem;
	int			len;

	len = 0;
	if (!*argv)
		return (NULL);
	elem = malloc(sizeof(t_lst));
	elem->file = ft_strdup(*argv);
	if (ft_glob(NULL)->maxlen < (len = ft_strlen(*argv)))
		ft_glob(NULL)->maxlen = len;
	elem->start = start;
	elem->crrnt = start;
	elem->slctd = 0;
	elem->no = number;
	elem->prev = prev;
	elem->next = create_list(++argv, 0, elem, ++number);
	return (elem);
}

static t_lst	*circular(t_lst *list)
{
	t_lst	*end;

	end = list;
	while (end->next)
		end = end->next;
	list->prev = end;
	end->next = list;
	return (list);
}

t_lst			*ft_parse(char **argv)
{
	if (!argv || !*argv || !**argv)
		return (NULL);
	return (circular(create_list(argv, 1, NULL, 0)));
}

void			free_list(t_lst *list)
{
	t_lst *tmp;

	tmp = list ? list->next : list;
	while (tmp)
	{
		list = tmp->next;
		if (tmp->start)
			break ;
		free(tmp->file);
		free(tmp);
		tmp = list;
	}
	free(tmp->file);
	free(tmp);
}
