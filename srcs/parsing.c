/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 14:49:48 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/21 15:17:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <stdlib.h>

#include <string.h>
#include <stdio.h>

t_list	*create_list(char **argv, int start, t_list *prev)
{
	t_list *elem;

	if (!*argv)
		return (NULL);
	elem = malloc(sizeof(t_list));
	elem->file = strdup(*argv);
	elem->start = start;
	elem->prev = prev;
	elem->next = create_list(++argv, 0, elem);
	return (elem);
}

t_list	*ft_parse(char **argv)
{
	if (!argv || !*argv || !**argv)
		return (NULL);
	return (create_list(argv));
}

void	free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	show_list(t_list *list)
{
	t_list *cpy;

	cpy = list;
	while (cpy)
	{
		printf("%s\n", cpy->file);
		cpy = cpy->next;
	}
}

int main(int ac, char **av)
{
	t_list *list;

	list = ft_parse(av);
	show_list(list);
	free_list(list);
	return 0;
}