/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 15:25:39 by rclanget          #+#    #+#             */
/*   Updated: 2017/01/08 20:51:19 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

int				ft_exit(void)
{
	stat_cursor(1);
	set_term(GET(sauv));
	close(ft_glob(NULL)->out_fd);
	free_list(GET(list));
	free(ft_glob(NULL));
	exit(0);
	return (1);
}

int				ft_init(void)
{
	char			*name_term;
	struct termios	term;

	if (!(name_term = getenv("TERM")) || (tgetent(NULL, name_term) == -1))
	{
		ft_putendl_fd(YLW"Bad term"RESET, 2);
		return (0);
	}
	if (tcgetattr(0, &term) == -1)
		return (0);
	ft_memcpy(&ft_glob(NULL)->sauv, &term, sizeof(struct termios));
	get_canon(term);
	stat_cursor(0);
	handle_signal();
	handle_winch(-1);
	return (1);
}

int				main(int argc, char **argv)
{
	t_select	*info;
	int			ret;

	ret = 0;
	if (argc > 1)
	{
		argv++;
		if (!(info = (t_select *)malloc(sizeof(t_select))))
			return (1);
		if (!(ft_glob(info)) ||
			(ft_out_fd() == -1) ||
			!(ft_glob(NULL)->list = ft_parse(argv)) ||
			!ft_init())
				return (1);
		looping();
	}
	else
	{
		ft_putendl_fd(YLW"One or more argument is necessary"RESET, 2);
			return (1);
	}
	return (0);
}
