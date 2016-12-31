/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/23 10:45:59 by rclanget          #+#    #+#             */
/*   Updated: 2016/12/31 16:48:46 by rclanget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

#include <fcntl.h>

int		ft_out_fd(void)
{
	char	*tty_name;
	int		ret;

	tty_name = ttyname(0);
	ret = 1;
	if ((ft_glob(NULL)->out_fd = open(tty_name, O_WRONLY)) == -1)
		ret = -1;
	free(tty_name);
	return (ret);
}
