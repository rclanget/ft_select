/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:09:49 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:09:50 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <inttypes.h>
#include <stddef.h>

static t_lli			get_iarg(int info, va_list list)
{
	t_lli ret;

	if (info & LGTH_HH)
		ret = (t_lli)(signed char)va_arg(list, int);
	else if (info & LGTH_H)
		ret = (t_lli)(short)va_arg(list, int);
	else if (info & LGTH_L)
		ret = (t_lli)va_arg(list, long);
	else if (info & LGTH_LL)
		ret = (t_lli)va_arg(list, long long);
	else if (info & LGTH_J)
		ret = (t_lli)va_arg(list, intmax_t);
	else if (info & LGTH_Z)
		ret = (t_lli)va_arg(list, size_t);
	else
		ret = (t_lli)va_arg(list, int);
	return (ret);
}

static t_ulli			get_uarg(int info, va_list list)
{
	t_ulli ret;

	if (info & LGTH_HH)
		ret = (t_ulli)(unsigned char)va_arg(list, unsigned int);
	else if (info & LGTH_H)
		ret = (t_ulli)(unsigned short)va_arg(list, unsigned int);
	else if (info & LGTH_L)
		ret = (t_ulli)va_arg(list, unsigned long);
	else if (info & LGTH_LL)
		ret = (t_ulli)va_arg(list, unsigned long long);
	else if (info & LGTH_J)
		ret = (t_ulli)va_arg(list, uintmax_t);
	else if (info & LGTH_Z)
		ret = (t_ulli)va_arg(list, size_t);
	else
		ret = (t_ulli)va_arg(list, unsigned int);
	return (ret);
}

static t_number			get_number_syntax(t_conv conv, t_lli i)
{
	t_number syntax;

	syntax.sign_char = (conv.info & FLAG_S) ? ' ' : 0;
	syntax.sign_char = (conv.info & FLAG_P) ? '+' : syntax.sign_char;
	syntax.sign_char = (i < 0) ? '-' : syntax.sign_char;
	syntax.i = (i < 0) ? -i : i;
	syntax.base = 10;
	syntax.capitals = 0;
	pf_bzero(&(syntax.prefix), 5);
	syntax.paddc = ((conv.info & FLAG_Z) && !(conv.info & IS_PRE)) ? '0' : ' ';
	syntax.lajust = 0;
	if ((conv.info & FLAG_M) && (syntax.paddc = ' '))
		syntax.lajust = 1;
	syntax.width = conv.width;
	syntax.prec = conv.prec;
	return (syntax);
}

static t_number			get_unumber_syntax(t_conv conv, t_ulli i)
{
	t_number syntax;

	syntax.sign_char = 0;
	syntax.i = i;
	syntax.base = 10;
	syntax.capitals = conv.capitals;
	pf_bzero(&(syntax.prefix), 5);
	if ((conv.type == 'x' || conv.type == 'X') &&
		(syntax.base = 16) && i && (conv.info & FLAG_D))
		pf_strcat(syntax.prefix, (conv.type == 'x') ? "0x" : "0X");
	if (conv.type == 'o' && (syntax.base = 8) && i && (conv.info & FLAG_D))
		pf_strcat(syntax.prefix, "0");
	if (conv.type == 'p' && (syntax.base = 16))
		pf_strcat(syntax.prefix, "0x");
	syntax.paddc = ((conv.info & FLAG_Z) && !(conv.info & IS_PRE)) ? '0' : ' ';
	syntax.lajust = 0;
	if ((conv.info & FLAG_M) && (syntax.paddc = ' '))
		syntax.lajust = 1;
	syntax.width = conv.width;
	syntax.prec = conv.prec;
	return (syntax);
}

int						print_int(t_conv conv, va_list list, char type)
{
	t_lli		i;
	t_ulli		u;
	t_number	syntax;

	if (type == 'i')
	{
		i = get_iarg(conv.info, list);
		syntax = get_number_syntax(conv, i);
	}
	else if (type == 'u' || type == 'p')
	{
		u = (type == 'u') ? get_uarg(conv.info, list) :
		(t_ulli)va_arg(list, unsigned long);
		syntax = get_unumber_syntax(conv, u);
	}
	return (ft_print_number(syntax));
}
