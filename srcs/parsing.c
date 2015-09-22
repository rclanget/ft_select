/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 14:49:48 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 13:39:43 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

#include <stdlib.h>

t_lst	*create_list(char **argv, int start, t_lst *prev, int number)
{
	t_lst 	*elem;
	int 	len;

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

t_lst	*circular(t_lst *list)
{
	t_lst	*end;

	end = list;
	while (end->next)
		end = end->next;
	list->prev = end;
	end->next = list;
	return (list);
}

t_lst	*ft_parse(char **argv)
{
	if (!argv || !*argv || !**argv)
		return (NULL);
	return (circular(create_list(++argv, 1, NULL, 0)));
}

void	free_list(t_lst *list)
{
	while ((list = list->next))
	{
		if (list->start)
			break ;
		free(list->file);
		free(list);
	}
	free(list->file);
	free(list);
}
