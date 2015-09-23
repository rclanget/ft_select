/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:10:38 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:10:40 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_wctoc(wchar_t c, char buf[5])
{
	pf_bzero(buf, 5);
	if (c < 0x80)
		buf[0] = c;
	else if (c < 0x800)
	{
		buf[0] = ((c >> 6) & 0x1F) | 0xC0;
		buf[1] = (c & 0x3F) | 0x80;
	}
	else if (c < 0x10000)
	{
		buf[0] = ((c >> 12) & 0xF) | 0xE0;
		buf[1] = ((c >> 6) & 0x3F) | 0x80;
		buf[2] = ((c & 0x3F)) | 0x80;
	}
	else if (c < 0x110000)
	{
		buf[0] = ((c >> 18) & 0x7) | 0xF0;
		buf[1] = ((c >> 12) & 0x3F) | 0x80;
		buf[2] = ((c >> 6) & 0x3F) | 0x80;
		buf[3] = ((c >> 0) & 0x3F) | 0x80;
	}
	return (pf_strlen(buf));
}

int			ft_wstrlen(wchar_t *wchar)
{
	int		i;
	wchar_t	c;
	char	buf[5];

	i = 0;
	while (*wchar)
	{
		i += ft_wctoc(c = *wchar, buf);
		wchar++;
	}
	return (i);
}

int			ft_wnstrlen(wchar_t *wchar, int limit)
{
	int		i;
	int		len;
	char	buf[5];

	i = 0;
	while (*wchar)
	{
		len = ft_wctoc(*wchar, buf);
		if (limit != -1 && (i + len) > limit)
			break ;
		i += len;
		wchar++;
	}
	return (i);
}
