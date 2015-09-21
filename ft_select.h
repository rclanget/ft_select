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

#endif