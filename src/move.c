/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:05 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:06 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		left(t_win *win)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = win->plr->dirX;
	oldPlaneX = win->plr->planeX;
	win->plr->dirX = win->plr->dirX
			* cos(-win->plr->rotation) - win->plr->dirY
			* sin(-win->plr->rotation);
	win->plr->dirY = oldDirX * sin(-win->plr->rotation)
			+ win->plr->dirY * cos(-win->plr->rotation);
	win->plr->planeX = win->plr->planeX
			* cos(-win->plr->rotation) - win->plr->planeY
			* sin(-win->plr->rotation);
	win->plr->planeY = oldPlaneX
			* sin(-win->plr->rotation) + win->plr->planeY
			* cos(-win->plr->rotation);
}

static void		right(t_win *win)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = win->plr->dirX;
	oldPlaneX = win->plr->planeX;
	win->plr->dirX = win->plr->dirX
			* cos(win->plr->rotation) - win->plr->dirY
			* sin(win->plr->rotation);
	win->plr->dirY = oldDirX * sin(win->plr->rotation)
			+ win->plr->dirY * cos(win->plr->rotation);
	win->plr->planeX = win->plr->planeX
			* cos(win->plr->rotation) - win->plr->planeY
			* sin(win->plr->rotation);
	win->plr->planeY = oldPlaneX
			* sin(win->plr->rotation) + win->plr->planeY
			* cos(win->plr->rotation);
}
static void		forward(t_win *win)
{
	if (win->map[(int)win->plr->posY]
		[(int)(win->plr->posX + win->plr->dirX
		* win->plr->speed)] == '0')
		win->plr->posX += win->plr->dirX
		* win->plr->speed;
	if (win->map[(int)(win->plr->posY
		+ win->plr->dirY * win->plr->speed)]
		[(int)win->plr->posX] == '0')
		win->plr->posY += win->plr->dirY
		* win->plr->speed;
}

static void		backward(t_win *win)
{
	if (win->map[(int)win->plr->posY]
		[(int)(win->plr->posX - win->plr->dirX
		* win->plr->speed)] == '0')
		win->plr->posX -= win->plr->dirX
		* win->plr->speed;
	if (win->map[(int)(win->plr->posY
		- win->plr->dirY * win->plr->speed)]
		[(int)win->plr->posX] == '0')
		win->plr->posY -= win->plr->dirY
		* win->plr->speed;
}

int 	      move_events(int key, t_win *win)
{
	if (key == A || key == _LEFT)
		left(win);
	else if (key == D || key == _RIGHT)
		right(win);
	else if (key == W || key == _UP)
		forward(win);
	else if (key == S || key == _DOWN)
		backward(win);
	else if (key == ESC)
		mlx_destroy_window(win->mlx, win->win);
	return (SUCCESS);
}
