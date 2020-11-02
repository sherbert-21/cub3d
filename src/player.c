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

static void	set_camera(t_game *win, double dirX,
                          double planeX, double planeY)
{
	win->plr->dirX = dirX;
	win->plr->planeX = planeX;
	win->plr->planeY = planeY;
}

int		set_pos(t_game *win, char dir, int x, int y)
{
	if (!win->plr)
		init_player(win);
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
	win->plr->posX = (double)(x - 1) + 0.5;
	win->plr->posY = (double)y + 0.5;
	return (SUCCESS);
}
