/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:09:39 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:40 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>
#include <float.h>
#include <math.h>

#define BUFLEN 128

static long double		get_arg(int info, va_list list)
{
	long double			ret_value;

	if (info & LGTH_GL)
		ret_value = va_arg(list, long double);
	else
		ret_value = va_arg(list, double);
	return (ret_value);
}

static int				check_inf_nan(int info, long double i)
{
	if (isinf(i) && i > 0)
		return (ft_printf((info & LGTH_GL) ? "inf" : "INF"));
	if (isinf(i) && i < 0)
		return (ft_printf((info & LGTH_GL) ? "-inf" : "-INF"));
	if (isnan(i))
		return (ft_printf((info & LGTH_GL) ? "nan" : "NAN"));
	return (0);
}

int						print_double(t_conv conv, va_list list)
{
	long double			i;
	t_lli				left;
	static char			fmt[BUFLEN];

	pf_bzero(&fmt, BUFLEN);
	i = get_arg(conv.info, list);
	if (isinf(i) || isnan(i))
		return (check_inf_nan(conv.info, i));
	left = (t_lli)i;
	i = (i > 0) ? i : -i;
	i -= (t_lli)i;
	conv.prec = (conv.info & IS_PRE) ? conv.prec : 6;
	pf_strcat(fmt, "%lld");
	if (conv.prec)
	{
		pf_strcat(fmt, ".%0");
		fmt[pf_strlen(fmt)] = '0' + conv.prec;
		pf_strcat(fmt, "lld");
		while (--conv.prec >= 0)
			i *= 10;
	}
	return (ft_printf(fmt, left,
	((i - (t_lli)i) * 10 >= 5) ? (t_lli)++i : (t_lli)i));
}

static int				get_form(long double *i)
{
	long double sign;
	int			expose;

	expose = 0;
	sign = (*i < 0) ? -1 : 1;
	*i = (*i > 0) ? *i : -*i;
	if (*i)
	{
		while (*i > 10 && ++expose)
			*i /= 10;
		while (*i < 1 && --expose)
			*i *= 10;
	}
	*i *= sign;
	return (expose);
}

int						print_scientific(t_conv conv, va_list list)
{
	long double			i;
	static char			fmt[BUFLEN];
	int					expose;

	pf_bzero(&fmt, BUFLEN);
	if (isinf(i = get_arg(conv.info, list)) || isnan(i))
		return (check_inf_nan(conv.info, i));
	expose = get_form(&i);
	pf_strcat(fmt, "%.");
	pf_strcat(fmt, pf_itoa((conv.info & IS_PRE) ? conv.prec : 6));
	pf_strcat(fmt, (conv.info & LGTH_L) ? "LfE%+.2d" : "Lfe%+.2d");
	return (ft_printf(fmt, i, expose));
}
