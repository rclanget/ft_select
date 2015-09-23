/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:10:02 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:10:06 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static void		*get_arg(int info, va_list list)
{
	void	*str;

	if (info & LGTH_L)
		str = (void *)va_arg(list, wchar_t *);
	else
		str = (void *)va_arg(list, char *);
	return (str);
}

static int		ft_print_str(t_conv conv, char *str)
{
	int		len;
	int		ret;
	char	paddc;

	ret = 0;
	len = pf_strlen(str);
	len = ((conv.info & IS_PRE) && len > conv.prec) ? conv.prec : len;
	conv.width -= len;
	paddc = (conv.info & FLAG_Z) ? '0' : ' ';
	while ((!(conv.info & FLAG_M)) && --conv.width >= 0)
		ret += write(ft_out(NULL), &paddc, 1);
	ret += write(ft_out(NULL), str, len);
	while ((conv.info & FLAG_M) && --conv.width >= 0)
		ret += write(ft_out(NULL), " ", 1);
	return (ret);
}

static int		ft_print_wstr(t_conv conv, wchar_t *str)
{
	int		len;
	int		ret;
	char	buf[5];

	ret = 0;
	len = ft_wnstrlen(str, (conv.info & IS_PRE) ? conv.prec : -1);
	conv.width -= len;
	while ((!(conv.info & FLAG_M)) && --conv.width >= 0)
		ret += write(ft_out(NULL), (conv.info & FLAG_Z) ? "0" : " ", 1);
	while (*str && (len -= ft_wctoc(*str, buf)) >= 0)
	{
		ft_wctoc(*str, buf);
		ret += write(ft_out(NULL), buf, pf_strlen(buf));
		str++;
	}
	while ((conv.info & FLAG_M) && --conv.width >= 0)
		ret += write(ft_out(NULL), " ", 1);
	return (ret);
}

int				print_str(t_conv conv, va_list list)
{
	void	*str;
	int		ret;

	ret = 0;
	if (!(str = get_arg(conv.info, list)))
	{
		if (!conv.width)
			ret = write(ft_out(NULL), "(null)", 6);
		else
			while (--conv.width >= 0)
				ret += write(ft_out(NULL), (conv.info & FLAG_Z) ? "0" : " ", 1);
	}
	if (str && conv.info & LGTH_L)
		ret = ft_print_wstr(conv, (wchar_t *)str);
	else if (str)
		ret = ft_print_str(conv, (char *)str);
	return (ret);
}
