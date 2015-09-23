/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/23 10:45:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/23 10:52:42 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <fcntl.h>

int		ft_out(void)
{
	if ((ft_glob(NULL)->out_fd = open(ttyname(0), O_WRONLY)) == -1)
		return (-1);
	return (1);
}