#ifndef FT_SELECT_H
# define FT_SELECT_H

#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct 		s_list
{
	char			*file;
	int 			start;
	int				select;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct 		s_select
{
	int 			line;
	int 			col;
	int				maxlen;
	struct termios	*sauv;
	t_list			*list;
}					t_select;

t_list				*ft_parse(char **argv);
t_select			*ft_glob(t_select *arg);

#endif