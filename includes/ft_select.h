/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:19:14 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 13:38:31 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct 		s_lst
{
	char			*file;
	int 			start;
	int				slctd;
	int				crrnt;
	int				dlted;
	int				no;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct 		s_select
{
	int 			line;
	int 			col;
	int				maxlen;
	struct termios	*sauv;
	t_lst			*list;
}					t_select;

t_lst				*ft_parse(char **argv);
t_select			*ft_glob(t_select *arg);
void				print_elem(t_select *elem);
void				get_size(void);
void				set_term(struct termios term);
void				get_canon(struct termios term);
void				clear_win(void);
void				get_size(void);
int					ft_putch(int c);
void				handle_winch(void);
int					looping(void);
void				handle_sigcont(void);
void				get_new_size(int i);
void				put_cursor(int i, int j);
void				stat_cursor(int stat);

#endif