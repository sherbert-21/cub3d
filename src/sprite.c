/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:54:00 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:54:01 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		next_sprite(t_sprites *old, t_sprites *new, t_ray *ray)
{
	while (1)
	{
		if (old->x == ray->mapX && old->y == ray->mapY)
		{
			free(new);
			break;
		}
		if ((old->x != ray->mapX || old->y != ray->mapY)
			&& !old->next)
		{
			old->next = new;
			break;
		}
		if (old->next)
			old = old->next;
		else
		{
			free(new);
			break;
		}
	}
}

void			is_sprite(t_ray *ray, t_game *win)
{
	t_sprites *new;
	t_sprites *old;
	t_sprites save;

	if (!(new = malloc(sizeof(t_sprites))))
		return ;
	new->next = NULL;
	new->x = ray->mapX;
	new->y = ray->mapY;
	old = win->sprite_screen;
	save = *old;
	if (old->x == -1 && old->y == -1)
	{
		old->x = ray->mapX;
		old->y = ray->mapY;
	}
	else
		next_sprite(old, new, ray);
	old = &save;
}

int				stock_sprite(char *path, t_game *win)
{
	if (!(win->sprite->img =
		mlx_xpm_file_to_image(win->mlx, path,
		&win->sprite->width,
		&win->sprite->height)))
		return (ERR);
	win->sprite->data =
		mlx_get_data_addr(win->sprite->img,
		&win->sprite->bpp,
		&win->sprite->size,
		&win->sprite->endian);
	return (SUCCESS);
}

void			sort_sprite(t_game *win, t_sprite *sprites, int nbr)
{
	int			i;
	double		dist_one;
	double		dist_two;
	t_sprite	tmp;

	i = 0;
	while (i < nbr && i + 1 != nbr)
	{
		dist_one = ((win->plr->posX - sprites[i].x)
		* (win->plr->posX - sprites[i].x) + (win->plr->posY
		- sprites[i].y) * (win->plr->posY - sprites[i].y));
		dist_two = ((win->plr->posX - sprites[i + 1].x)
		* (win->plr->posX - sprites[i + 1].x)
		+ (win->plr->posY - sprites[i + 1].y)
		* (win->plr->posY - sprites[i + 1].y));
		if (dist_one < dist_two)
		{
			tmp = sprites[i];
			sprites[i] = sprites[i + 1];
			sprites[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

t_sprite		*list_to_tab(t_game *win)
{
	t_sprite	*tmp;
	t_sprites	*save;
	int			count;

	save = win->sprite_screen;
	count = -1;
	if (!(tmp = malloc(sizeof(t_sprite)
		* ft_lstsize((t_list *)win->sprite_screen))))
		return (ERR);
	ft_bzero(tmp, sizeof(t_sprite)
		* ft_lstsize((t_list *)win->sprite_screen));
	while (++count > -1)
	{
		if (win->sprite_screen)
		{
			tmp[count].x = win->sprite_screen->x;
			tmp[count].y = win->sprite_screen->y;
		}
		if (win->sprite_screen->next)
			win->sprite_screen = win->sprite_screen->next;
		else
			break;
	}
	win->sprite_screen = save;
	return (tmp);
}
