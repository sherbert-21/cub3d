/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <sherbert@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 09:15:45 by rchallie          #+#    #+#             */
/*   Updated: 2020/10/25 02:02:13 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void			calcul_values(
	t_draw_sprite *ds,
	t_win *win
)
{
	ds->inv_det = 1.0 / (win->plr->planeX * win->plr->dirY
		- win->plr->dirX * win->plr->planeY);
	ds->transform_x = ds->inv_det * (win->plr->dirY * ds->sprite_x
		- win->plr->dirX * ds->sprite_y);
	ds->transform_y = ds->inv_det * (-win->plr->planeY * ds->sprite_x
		+ win->plr->planeX * ds->sprite_y);
	ds->sprite_screen_x = (int)((win->width / 2) * (1 + ds->transform_x
		/ ds->transform_y));
	ds->sprite_height = abs((int)(win->height / ds->transform_y));
	ds->draw_start_y = -ds->sprite_height / 2 + ((win->height / 2)
		* win->plr->cam_height);
	if (ds->draw_start_y < 0)
		ds->draw_start_y = 0;
	ds->draw_end_y = ds->sprite_height / 2 + ((win->height / 2)
		* win->plr->cam_height);
	if (ds->draw_end_y >= win->height)
		ds->draw_end_y = win->height - 1;
	ds->sprite_width = abs((int)(win->height / ds->transform_y));
	ds->draw_start_x = -ds->sprite_width / 2 + ds->sprite_screen_x;
	if (ds->draw_start_x < 0)
		ds->draw_start_x = 0;
	ds->draw_end_x = ds->sprite_width / 2 + ds->sprite_screen_x;
	if (ds->draw_end_x >= win->width)
		ds->draw_end_x = win->width - 1;
	ds->stripe = ds->draw_start_x;
}

static void			pix_on_sprite_image(
	t_draw_sprite *ds,
	t_win *win
)
{
	ds->d = ds->y * win->sprite->size_line - (win->height
		* win->plr->cam_height)
		* (win->sprite->size_line / 2) + ds->sprite_height
		* win->sprite->size_line / 2;
	ds->tex_y = ((ds->d * win->sprite->height) / ds->sprite_height)
		/ win->sprite->size_line;
	ds->totcolor = win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8]
		+ win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8 + 1]
		+ win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8 + 2];
}

static void			is_black(
	t_draw_sprite *ds,
	t_win *win
)
{
	win->img->data[ds->y * win->img->size_line
		+ ds->stripe * win->img->bpp / 8] =
		win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8];
	win->img->data[ds->y * win->img->size_line
		+ ds->stripe * win->img->bpp / 8 + 1] =
		win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8 + 1];
	win->img->data[ds->y * win->img->size_line
		+ ds->stripe * win->img->bpp / 8 + 2] =
		win->sprite->data[ds->tex_y
		* win->sprite->size_line + ds->tex_x
		* win->sprite->bpp / 8 + 2];
}

static void			make_sprite(
	t_draw_sprite *ds,
	t_win *win,
	t_ray *ray
)
{
	ds->sprite_x = ds->sprites[ds->i].x - (win->plr->posx - 0.5);
	ds->sprite_y = ds->sprites[ds->i].y - (win->plr->posy - 0.5);
	calcul_values(ds, win);
	while (ds->stripe < ds->draw_end_x)
	{
		ds->tex_x = (int)(win->sprite->size_line * (ds->stripe
		- (-ds->sprite_width / 2 + ds->sprite_screen_x))
			* win->sprite->width / ds->sprite_width)
			/ win->sprite->size_line;
		if (ds->transform_y > 0 && ds->stripe > 0 && ds->stripe
			< win->width && ds->transform_y < ray->z_buffer[ds->stripe])
		{
			ds->y = ds->draw_start_y;
			while (ds->y < ds->draw_end_y)
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
		return (ERROR);
	ft_bzero(ds, sizeof(t_draw_sprite));
	ds->i = 0;
	ds->sprites = list_to_tab(win);
	sort_sprite(win, ds->sprites,
		ft_lstsize((t_list *)win->sprites_on_screen));
	while (ds->i < ft_lstsize((t_list *)win->sprites_on_screen))
	{
		make_sprite(ds, win, ray);
		ds->i++;
	}
	free(ds->sprites);
	return (SUCCES);
}
