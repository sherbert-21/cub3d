/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:52:07 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:52:08 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			init_plr(t_win *win)
{
	if (!(win->plr = malloc(sizeof(t_player))))
		return (invalid_file(0));
	ft_bzero(win->plr, sizeof(t_player));
	win->plr->posX = -20.0;
	win->plr->posY = -20.0;
	win->plr->speed = 0.13;
	win->plr->dirX = 1.0;
	win->plr->dirY = 0.0;
	win->plr->planeX = -20.0;
	win->plr->planeY = -20.0;
	win->plr->rotation = 0.13;
	return (SUCCESS);
}

int			init_keybuff(t_win *win)
{
	if (!(win->keybuff = malloc(sizeof(t_keybuff))))
		return (invalid_file(0));
	ft_bzero(win->keybuff, sizeof(t_keybuff));
	win->keybuff->forward = 0;
	win->keybuff->backward = 0;
	win->keybuff->left = 0;
	win->keybuff->right = 0;
    win->keybuff->turn_left = 0;
    win->keybuff->turn_right = 0;
	return (SUCCESS);
}

int			init_sprite(t_win *win)
{
	if (!(win->sprite = malloc(sizeof(t_pic))))
		return (invalid_file(0));
	ft_bzero(win->sprite, sizeof(t_pic));
	// if (!(win->sprites_on_screen = malloc(sizeof(t_list))))
	// 	return (1);
	// ft_bzero(win->sprites_on_screen, sizeof(t_list));
	// win->sprites_on_screen->x = -1;
	// win->sprites_on_screen->y = -1;
	return (SUCCESS);
}

int			init_text(t_win *win, int nbr)
{
	int i;

	i = 0;
	if (!(win->text = malloc(sizeof(t_pic *) * nbr + 1)))
		return (invalid_file(0));
	while (i < nbr)
	{
		if (!(win->text[i] = malloc(sizeof(t_pic))))
			return (invalid_file(0));
		ft_bzero(win->text[i], sizeof(t_pic));
		i++;
	}
	return (SUCCESS);
}
