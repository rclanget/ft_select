/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 14:49:48 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/21 15:40:05 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <stdlib.h>

// #include <string.h>
// #include <stdio.h>
// #include <unistd.h>

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

t_list	*circular(t_list *list)
{
	t_list	*end;

	end = list;
	while (end->next)
		end = end->next;
	list->prev = end;
	end->next = list;
	return (list);
}

t_list	*ft_parse(char **argv)
{
	if (!argv || !*argv || !**argv)
		return (NULL);
	return (circular(create_list(argv, 1, NULL)));
}

void	free_list(t_list *list)
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

// void	show_list(t_list *list)
// {
// 	t_list *cpy;

// 	cpy = list;
// 	while (cpy)
// 	{
// 		printf("%s\n", cpy->file);
// 		cpy = cpy->next;
// 		if (cpy->start)
// 			break ;
// 	}
// }

// int main(int ac, char **av)
// {
// 	t_list *list;

// 	list = ft_parse(av);
// 	show_list(list);
// 	free_list(list);
// 	sleep(10);
// 	return 0;
// }