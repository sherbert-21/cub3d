/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:13 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:14 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_camera(t_win *win, double dirX, 
							double planeX, double planeY)
{
	win->plr->dirX = dirX;
	win->plr->planeX = planeX;
	win->plr->planeY = planeY;
}

int		set_pos(t_win *win, char dir)
{
	if (!win->plr)
		init_plr(win);
	if (dir == 'E')
	{
		win->plr->dirY = 0.0;
		set_camera(win, 1.0, 0.0, 0.66);
	}
	else if (dir == 'W')
	{
		win->plr->dirY = 0.0;
		set_camera(win, -1.0, 0.0, -0.66);
	}
	else if (dir == 'N')
	{
		win->plr->dirY = -1.0;
		set_camera(win, 0.0, 0.66, 0.0);
	}
	else if (dir == 'S')
	{
		win->plr->dirY = 1.0;
		set_camera(win, 0.0, -0.66, 0.0);
	}
	return (SUCCESS);
}
