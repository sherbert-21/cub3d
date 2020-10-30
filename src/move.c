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
    if (win->map[(int)win->plr->posY]
        [(int)(win->plr->posX - win->plr->planeX
        * win->plr->speed)] == '0')
        win->plr->posX -= win->plr->planeX
        * win->plr->speed;
    if (win->map[(int)(win->plr->posY
        - win->plr->planeY * win->plr->speed)]
        [(int)win->plr->posX] == '0')
        win->plr->posY -= win->plr->planeY
        * win->plr->speed;
}

static void		right(t_win *win)
{
    if (win->map[(int)win->plr->posY]
        [(int)(win->plr->posX + win->plr->planeX
        * win->plr->speed)] == '0')
        win->plr->posX += win->plr->planeX
        * win->plr->speed;
    if (win->map[(int)(win->plr->posY
        + win->plr->planeY * win->plr->speed)]
        [(int)win->plr->posX] == '0')
        win->plr->posY += win->plr->planeY
        * win->plr->speed;
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
    if (key == A)
        left(win);
    else if (key == D)
        right(win);
	else if (key == _LEFT)
		turn_left(win);
	else if (key == _RIGHT)
		turn_right(win);
	else if (key == W)
		forward(win);
	else if (key == S)
		backward(win);
	else if (key == ESC)
		mlx_destroy_window(win->mlx, win->win);
	return (SUCCESS);
}
