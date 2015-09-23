/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:09:29 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:30 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>

int				ft_print_char(char c, t_conv conv)
{
	int		ret;
	char	paddc;

	ret = 0;
	conv.width--;
	paddc = (conv.info & FLAG_Z) ? '0' : ' ';
	while ((!(conv.info & FLAG_M)) && --conv.width >= 0)
		ret += write(ft_out(NULL), &paddc, 1);
	ret += write(ft_out(NULL), &c, 1);
	while ((conv.info & FLAG_M) && --conv.width >= 0)
		ret += write(ft_out(NULL), " ", 1);
	return (ret);
}

static int		ft_print_wchar(wchar_t c, t_conv conv)
{
	int		ret;
	char	paddc;
	char	buf[5];
	int		len;

	ret = 0;
	conv.width -= (len = ft_wctoc(c, buf));
	if (!len && len++)
		conv.width--;
	paddc = (conv.info & FLAG_Z) ? '0' : ' ';
	while ((!(conv.info & FLAG_M)) && --conv.width >= 0)
		ret += write(ft_out(NULL), &paddc, 1);
	ret += write(ft_out(NULL), buf, len);
	while ((conv.info & FLAG_M) && --conv.width >= 0)
		ret += write(ft_out(NULL), " ", 1);
	return (ret);
}

int				print_char(t_conv conv, va_list list)
{
	char	c;
	wchar_t	d;
	int		ret;

	if (conv.info & LGTH_L)
	{
		d = va_arg(list, wchar_t);
		ret = ft_print_wchar(d, conv);
	}
	else
	{
		c = (char)va_arg(list, int);
		ret = ft_print_char(c, conv);
	}
	return (ret);
}
