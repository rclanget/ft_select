/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:08:37 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:08:38 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>

t_conv				init_var(int nprinted)
{
	t_conv conv;

	conv.info = 0;
	conv.width = 0;
	conv.prec = -1;
	conv.type = 0;
	conv.ret = nprinted;
	conv.capitals = 0;
	return (conv);
}

t_conv				ft_modify(t_conv conv)
{
	if (conv.type == 'D' || conv.type == 'U' || conv.type == 'O' ||
		conv.type == 'S' || conv.type == 'C' || conv.type == 'F' ||
		conv.type == 'E')
	{
		conv.type += ('A' > 'a') ? 'A' - 'a' : 'a' - 'A';
		conv.info = ((conv.info >> 6) << 6) | LGTH_L;
	}
	if (conv.type == 'X')
		conv.capitals = 16;
	if (conv.type == 'o' && (conv.info & IS_PRE) &&
		(conv.info & FLAG_D) && !conv.prec)
		conv.prec = -1;
	if (conv.type == 'o' && (conv.info & IS_PRE) &&
		(conv.info & FLAG_D) && conv.prec)
		conv.prec--;
	return (conv);
}

int					print_conversion(t_conv conv, va_list list)
{
	int		nprinted;

	if (conv.type == 'd' || conv.type == 'i')
		nprinted = print_int(conv, list, 'i');
	else if (conv.type == 'o' || conv.type == 'u' ||
		conv.type == 'x' || conv.type == 'X')
		nprinted = print_int(conv, list, 'u');
	else if (conv.type == 's')
		nprinted = print_str(conv, list);
	else if (conv.type == 'p')
		nprinted = print_int(conv, list, 'p');
	else if (conv.type == 'c')
		nprinted = print_char(conv, list);
	else if (conv.type == 'f')
		nprinted = print_double(conv, list);
	else if (conv.type == 'k')
		nprinted = print_time(conv, list);
	else if (conv.type == 'e')
		nprinted = print_scientific(conv, list);
	else
		nprinted = ft_print_char(conv.type, conv);
	return (nprinted);
}

int					run_printf(const char *fmt, va_list list)
{
	t_conv conv;

	conv = init_var(0);
	while (*fmt)
	{
		conv = init_var(conv.ret);
		if (*fmt == '%')
		{
			if (!*(fmt = get_conv_info(fmt, &conv, list)))
				continue;
			conv.ret += print_conversion(ft_modify(conv), list);
			fmt++;
		}
		else
			conv.ret += write(ft_out(NULL), fmt++, 1);
	}
	return (conv.ret);
}

int					ft_printf(const char *fmt, ...)
{
	va_list		list;
	int			nprinted;

	nprinted = 0;
	if (fmt)
	{
		ft_out("1");
		va_start(list, fmt);
		nprinted = run_printf(fmt, list);
		va_end(list);
	}
	return (nprinted);
}
