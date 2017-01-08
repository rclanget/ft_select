/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 17:19:14 by rclanget          #+#    #+#             */
/*   Updated: 2017/01/08 20:00:12 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <stdlib.h>

# define OPT_I		0x1

# define GET(x)		ft_glob(NULL)->x
# define SET(x, y)	ft_glob(NULL)->x = y
# define PUT(x)		ft_fdprint(GET(out_fd), tgetstr(x, NULL));

# define RED		"\x1B[31;1m"
# define CYN		"\x1B[36;1m"
# define WHT		"\x1B[37;1m"
# define YLW		"\033[33;40m"
# define RESET		"\x1B[0m"

typedef struct		s_lst
{
	char			*file;
	int				start;
	int				slctd;
	int				crrnt;
	int				dlted;
	int				no;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct		s_select
{
	int				line;
	int				col;
	int				maxlen;
	int				out_fd;
	struct termios	sauv;
	t_lst			*list;
	int				option;
}					t_select;

t_lst				*ft_parse(char **argv);
t_select			*ft_glob(t_select *arg);
void				print_elem(t_lst *list, int i, int j);
void				get_size(void);
void				set_term(struct termios term);
void				get_canon(struct termios term);
void				clear_win(void);
void				get_size(void);
int					ft_putch(int c);
int					looping(void);
void				put_cursor(int i, int j);
void				stat_cursor(int stat);
void				free_list(t_lst *list);
int					ft_exit(void);
int					ft_out_fd(void);
void				handle_winch(int i);
void				handle_signal(void);
int					ft_init(void);

#endif
