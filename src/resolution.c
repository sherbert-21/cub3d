/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:30 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:31 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            atoi_resol(char *ident, t_win *win, int z)
{
    if (z == 'x')
    {
        win->x = ft_atoi(ident);
        if (win->x > 1920)
            win->x = 1920;
    }
    else
    {
        win->y = ft_atoi(ident);
        if (win->y > 1080)
            win->y = 1080;
    }
}

int				resolution(char *ident, int i, t_win *win)
{
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i] == '0' || !ident[i])
		return (invalid_file(5, win));
	atoi_resol(&ident[i], win, 'x');
	while (ft_isdigit(ident[i]))
		i++;
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i] == '0' || !ident[i])
		return (invalid_file(5, win));
    atoi_resol(&ident[i], win, 'y');
	while (ft_isdigit(ident[i]))
		i++;
	while (ident[i] == ' ' && ident[i])
		i++;
	if (ident[i])
		return (invalid_file(5, win));
	return (SUCCESS);
}
