/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conv_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:09:18 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:19 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*get_flags(const char *fmt, t_conv *conv)
{
	while (*fmt)
	{
		if (*fmt == '#')
			conv->info |= FLAG_D;
		else if (*fmt == '+')
			conv->info |= FLAG_P;
		else if (*fmt == ' ')
			conv->info |= FLAG_S;
		else if (*fmt == '-')
			conv->info |= FLAG_M;
		else if (*fmt == '0')
			conv->info |= FLAG_Z;
		else
			break ;
		fmt++;
	}
	return (fmt);
}

static const char	*get_width(const char *fmt, t_conv *conv, va_list list)
{
	while (42)
	{
		if (*fmt <= '9' && *fmt >= '0' && (conv->info |= IS_WID))
		{
			conv->width = 0;
			while (*fmt <= '9' && *fmt >= '0')
				conv->width = 10 * conv->width + (*fmt++ - '0');
		}
		else if (*fmt == '*' && (conv->info |= IS_WID))
		{
			conv->width = va_arg(list, int);
			if (conv->width < 0 && (conv->width = -conv->width))
				conv->info |= FLAG_M;
			fmt++;
		}
		else
			break ;
	}
	return (fmt);
}

static const char	*get_precision(const char *fmt, t_conv *conv, va_list list)
{
	if (*fmt == '.' && fmt++)
	{
		conv->prec = 0;
		conv->info |= IS_PRE;
		while (42)
		{
			if ('0' <= *fmt && *fmt <= '9')
				while ('0' <= *fmt && *fmt <= '9')
					conv->prec = conv->prec * 10 + (*fmt++ - '0');
			else if (*fmt == '*')
			{
				conv->prec = va_arg(list, int);
				if (conv->prec < 0 && (conv->prec = -1))
					conv->info ^= IS_PRE;
				fmt++;
			}
			else
				break ;
		}
	}
	return (fmt);
}

static const char	*get_length(const char *fmt, t_conv *conv)
{
	if (*fmt == 'h' && fmt++)
		conv->info |= (*fmt == 'h' && fmt++) ? LGTH_HH : LGTH_H;
	else if (*fmt == 'l' && fmt++)
		conv->info |= (*fmt == 'l' && fmt++) ? LGTH_LL : LGTH_L;
	else if (*fmt == 'j' && fmt++)
		conv->info |= LGTH_J;
	else if (*fmt == 'z' && fmt++)
		conv->info |= LGTH_Z;
	else if (*fmt == 'L' && fmt++)
		conv->info |= LGTH_GL;
	return (fmt);
}

const char			*get_conv_info(const char *fmt, t_conv *conv, va_list list)
{
	fmt++;
	fmt = get_flags(fmt, conv);
	fmt = get_width(fmt, conv, list);
	fmt = get_precision(fmt, conv, list);
	fmt = get_length(fmt, conv);
	if (*fmt)
		conv->type = *fmt;
	return (fmt);
}
