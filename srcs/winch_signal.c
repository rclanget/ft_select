/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winch_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:24:20 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/21 17:31:09 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void		get_new_size(int i)
{
	get_size();
	print_elem(ft_glob(NULL)->list);
}

void		handle_winch(void)
{
	signal(SIGWINCH, get_new_size);
}