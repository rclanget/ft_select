/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcont.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:25:32 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/22 13:27:56 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

#include <signal.h>

void	handle_sigcont(void)
{
	signal(SIGCONT, get_new_size);
}