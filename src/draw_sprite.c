/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:48:37 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:48:40 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			calcul_values(
	t_draw_sprite *ds,
	t_win *win
)
{
	ds->invDet = 1.0 / (win->plr->planeX * win->plr->dirY
		- win->plr->dirX * win->plr->planeY);
	ds->transformX = ds->invDet * (win->plr->dirY * ds->spriteX
		- win->plr->dirX * ds->spriteY);
	ds->transformY = ds->invDet * (-win->plr->planeY * ds->spriteX
		+ win->plr->planeX * ds->spriteY);
	ds->spriteScreenX = (int)((win->x / 2) * (1 + ds->transformX
		/ ds->transformY));
	ds->height = abs((int)(win->y / ds->transformY));
	ds->drawStartY = -ds->height / 2 + win->y / 2;
	if (ds->drawStartY < 0)
		ds->drawStartY = 0;
	ds->drawEndY = ds->height / 2 + win->y / 2;
	if (ds->drawEndY >= win->y)
		ds->drawEndY = win->y - 1;
	ds->width = abs((int)(win->y / ds->transformY));
	ds->drawStartX = -ds->width / 2 + ds->spriteScreenX;
	if (ds->drawStartX < 0)
		ds->drawStartX = 0;
	ds->drawEndX = ds->width / 2 + ds->spriteScreenX;
	if (ds->drawEndX >= win->x)
		ds->drawEndX = win->x - 1;
	ds->stripe = ds->drawStartX;
}

static void			pix_on_sprite_image(
	t_draw_sprite *ds,
	t_win *win
)
{
	ds->d = ds->y * win->sprite->size - win->y
		* (win->sprite->size / 2) + ds->height
		* win->sprite->size / 2;
	ds->texY = ((ds->d * win->sprite->height) / ds->height)
		/ win->sprite->size;
	ds->totcolor = win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8]
		+ win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8 + 1]
		+ win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8 + 2];
}

static void			is_black(
	t_draw_sprite *ds,
	t_win *win
)
{
	win->screen->data[ds->y * win->screen->size
		+ ds->stripe * win->screen->bpp / 8] =
		win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8];
	win->screen->data[ds->y * win->screen->size
		+ ds->stripe * win->screen->bpp / 8 + 1] =
		win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8 + 1];
	win->screen->data[ds->y * win->screen->size
		+ ds->stripe * win->screen->bpp / 8 + 2] =
		win->sprite->data[ds->texY
		* win->sprite->size + ds->texX
		* win->sprite->bpp / 8 + 2];
}

static void			make_sprite(
	t_draw_sprite *ds,
	t_win *win,
	t_ray *ray
)
{
	ds->spriteX = ds->sprites[ds->i].x - (win->plr->posX - 0.5);
	ds->spriteY = ds->sprites[ds->i].y - (win->plr->posY - 0.5);
	calcul_values(ds, win);
	while (ds->stripe < ds->drawEndX)
	{
		ds->texX = (int)(win->sprite->size * (ds->stripe
		- (-ds->width / 2 + ds->spriteScreenX))
			* win->sprite->width / ds->width)
			/ win->sprite->size;
		if (ds->transformY > 0 && ds->stripe > 0 && ds->stripe
			< win->x && ds->transformY < ray->z_buffer[ds->stripe])
		{
			ds->y = ds->drawStartY;
			while (ds->y < ds->drawEndY)
			{
				pix_on_sprite_image(ds, win);
				if (ds->totcolor != 0)
					is_black(ds, win);
				ds->y++;
			}
		}
		ds->stripe++;
	}
}

int					draw_sprite(
	t_ray *ray,
	t_win *win
)
{
	t_draw_sprite *ds;

	if (!(ds = malloc(sizeof(t_draw_sprite))))
		return (ERR);
	ft_bzero(ds, sizeof(t_draw_sprite));
	ds->i = 0;
	ds->sprites = list_to_tab(win);
	sort_sprite(win, ds->sprites,
		ft_lstsize((t_list *)win->sprite_screen));
	while (ds->i < ft_lstsize((t_list *)win->sprite_screen))
	{
		make_sprite(ds, win, ray);
		ds->i++;
	}
	free(ds->sprites);
	return (SUCCESS);
}
