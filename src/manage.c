/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:52:46 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:52:47 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (key == ESC)
		exit(0);
	else if (key == W && win->keybuff->forward == 0)
		win->keybuff->forward = 1;
	else if (key == S && win->keybuff->backward == 0)
		win->keybuff->backward = 1;
	else if (key == A && win->keybuff->left == 0)
		win->keybuff->left = 1;
	else if (key == D && win->keybuff->right == 0)
		win->keybuff->right = 1;
    else if (key == _LEFT && win->keybuff->left == 0)
        win->keybuff->turn_left = 1;
    else if (key == _RIGHT && win->keybuff->right == 0)
        win->keybuff->turn_right = 1;
	return (SUCCESS);
}

int		key_released(int key, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if ((key == W) && win->keybuff->forward == 1)
		win->keybuff->forward = 0;
	else if ((key == S) && win->keybuff->backward == 1)
		win->keybuff->backward = 0;
	else if (key == A && win->keybuff->left == 1)
		win->keybuff->left = 0;
	else if (key == D && win->keybuff->right == 1)
		win->keybuff->right = 0;
    else if (key == _LEFT && win->keybuff->left == 1)
        win->keybuff->turn_left = 0;
    else if (key == _RIGHT && win->keybuff->right == 1)
        win->keybuff->turn_right = 0;
	return (0);
}
//
//int		destroy_window(void *param)
//{
//    t_win *win;
//
//    win = (t_win *)param;
//    mlx_destroy_window(win->mlx, win->win);
//    return (SUCCESS);
//}

static int		draw(t_win *win)
{
    if (!(ray(win)))
        return (invalid_file(10, win));
    return (SUCCESS);
}

int				loop(t_win *win)
{
    int   succ;

    move_events(win);
    succ = draw(win);
    return (succ);
}
