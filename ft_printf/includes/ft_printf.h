/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 15:07:55 by rclanget          #+#    #+#             */
/*   Updated: 2015/09/18 15:07:56 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FLAG_M					0x2000
# define FLAG_P					0x1000
# define FLAG_S					0x0800
# define FLAG_D					0x0400
# define FLAG_Z					0X0200

# define IS_WID					0x0100

# define IS_PRE					0x0080

# define LGTH_GL				0x0040
# define LGTH_HH				0X0020
# define LGTH_H					0x0010
# define LGTH_L					0x0008
# define LGTH_LL				0x0004
# define LGTH_J					0x0002
# define LGTH_Z					0x0001

# include <stdarg.h>
# include <wchar.h>

typedef long long int			t_lli;
typedef unsigned long long int	t_ulli;

typedef struct					s_conv
{
	int							info;
	int							width;
	int							prec;
	char						type;
	int							ret;
	va_list						list;
	int							capitals;
}								t_conv;

typedef struct					s_number
{
	t_ulli						i;
	int							base;
	char						prefix[5];
	int							capitals;
	char						sign_char;
	char						paddc;
	int							lajust;
	int							width;
	int							prec;
}								t_number;

void							pf_bzero(void *s, unsigned int n);
char							*pf_strcat(char *dest, const char *src);
int								pf_strlen(char *s);
char							*pf_itoa(long long int i);

int								ft_print_number(t_number s);
int								print_int(t_conv conv, va_list list, char type);

int								print_str(t_conv conv, va_list list);

int								ft_wstrlen(wchar_t *wchar);
int								ft_wnstrlen(wchar_t *wchar, int limit);
int								ft_wctoc(wchar_t c, char buf[5]);

int								ft_print_char(char c, t_conv conv);
int								print_char(t_conv conv, va_list list);

int								print_double(t_conv conv, va_list list);
int								print_scientific(t_conv conv, va_list list);

int								print_time(t_conv conv, va_list list);

const char						*get_conv_info
								(const char *fmt, t_conv *conv, va_list list);

int								ft_printf(const char *fmt, ...);
int								ft_fdprintf(int fd, const char *fmt, ...);

int								ft_out(char *output);
t_conv							init_var(int nprinted);
t_conv							ft_modify(t_conv conv);
int								print_conversion(t_conv conv, va_list list);
int								run_printf(const char *fmt, va_list list);

#endif
