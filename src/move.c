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

static void		left(t_game *win)
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

static void		right(t_game *win)
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
static void		forward(t_game *win)
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

static void		backward(t_game *win)
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

int 	      move_events(t_game *win)
{
    if (win->keybuff->left == 1)
        left(win);
    else if (win->keybuff->right == 1)
        right(win);
	else if (win->keybuff->turn_left == _LEFT)
		turn_left(win);
	else if (win->keybuff->turn_right == _RIGHT)
		turn_right(win);
	else if (win->keybuff->forward == W)
		forward(win);
	else if (win->keybuff->backward == S)
		backward(win);
	return (SUCCESS);
}
