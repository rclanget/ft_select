/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/29 16:17:39 by rclanget          #+#    #+#             */
/*   Updated: 2017/01/08 19:47:57 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"
#include <sys/stat.h>

static int		ft_file_which_type(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
		return (1);
	if (S_ISDIR(path_stat.st_mode))
		return (2);
	else
		return (0);
}

void			put_cursor(int i, int j)
{
	char	*gotostr;

	gotostr = tgetstr("cm", NULL);
	ft_putstr_fd(tgoto(gotostr, j, i), ft_glob(NULL)->out_fd);
}

static int		print_file(t_lst *file)
{
	int		color;

	if (file->crrnt)
		PUT("us");
	if (file->slctd)
		PUT("so");
	if (!file->dlted)
	{
		color = ft_file_which_type(file->file);
		if (color == 1)
			ft_fdprint(GET(out_fd), CYN"%s"RESET, file->file);
		else if (color == 2)
			ft_fdprint(GET(out_fd), RED"%s"RESET, file->file);
		else
			ft_fdprint(GET(out_fd), WHT"%s"RESET, file->file);
	}
	if (file->crrnt)
		PUT("ue");
	if (file->slctd)
		PUT("se");
	return (1);
}

static void		next_col(int *i, int *j)
{
	if (*i == GET(line))
	{
		*i = 0;
		*j += GET(maxlen) + 1;
	}
}

void			print_elem(t_lst *list, int i, int j)
{
	t_lst	*begin;
	int		current;
	int		files;

	files = 0;
	current = 0;
	begin = list;
	clear_win();
	while (1)
	{
		current = (!current && begin->crrnt) ? 1 : current;
		next_col(&i, &j);
		if (!begin->dlted)
		{
			files++;
			print_file(begin);
			put_cursor(i++, j);
		}
		if ((j + GET(maxlen)) > GET(col) || (begin = begin->next)->start)
			break ;
	}
	if (!files)
		ft_exit();
	current ? put_cursor(GET(line) + 1, 0) : print_elem(begin->next, 1, 0);
}
