/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:08:06 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:08:07 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_out(char *output)
{
	static int		ret;

	if (output)
		ret = output[0] - '0';
	return (ret);
}

int					ft_fdprintf(int fd, const char *fmt, ...)
{
	va_list		list;
	int			nprinted;

	nprinted = 0;
	if (fmt)
	{
		ft_out(pf_itoa((long long int)fd));
		va_start(list, fmt);
		nprinted = run_printf(fmt, list);
		va_end(list);
	}
	return (nprinted);
}
