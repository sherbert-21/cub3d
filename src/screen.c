/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:37 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:38 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pixel_put(int clr, int x, int y, t_pic *screen)
{
	unsigned char *src;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	src = (unsigned char *)&clr;
	r = src[0];
	g = src[1];
	b = src[2];
	screen->data[y * screen->size + x * screen->bpp / 8] = r;
	screen->data[y * screen->size + x * screen->bpp / 8 + 1] = g;
	screen->data[y * screen->size + x * screen->bpp / 8 + 2] = b;
}

void		ver_line_clr_image(t_line *line, t_win *win, int clr)
{
	int y;
	int y_max;

	if (line->y0 < line->y1)
	{
		y = line->y0;
		y_max = line->y1;
	}
	else
	{
		y = line->y1;
		y_max = line->y0;
	}
	if (y >= 0)
	{
		while (y < y_max)
		{
			pixel_put(clr, line->x, y, win->screen);
			y++;
		}
	}
}

static void	text_on_screen(t_line *line, t_pic *text, t_win *win, t_ray *ray)
{
	int d;

	d = line->y * text->size - win->x * text->size
		/ 2 + ray->lineHeight * text->size / 2;
	line->texY = ((d * text->height) / ray->lineHeight)
		/ text->size;
	win->screen->data[line->y * win->screen->size + line->x
					* win->screen->bpp / 8] = text->data[line->texY
					* text->size + line->texX * (text->bpp / 8)];
	win->screen->data[line->y * win->screen->size + line->x
					* win->screen->bpp / 8 + 1] = text->data[line->texY
					* text->size + line->texX * (text->bpp / 8)
					+ 1];
	win->screen->data[line->y * win->screen->size + line->x
					* win->screen->bpp / 8 + 2] = text->data[line->texY
					* text->size + line->texX * (text->bpp / 8)
					+ 2];
}

void		ver_line_text_pic(t_line *line, t_win *win, 
								t_pic *text, t_ray *ray)
{
	int y_max;

	if (line->y0 < line->y1)
	{
		line->y = line->y0;
		y_max = line->y1;
	}
	else
	{
		line->y = line->y1;
		y_max = line->y0;
	}
	if (line->y >= 0)
	{
		while (line->y < y_max)
		{
			text_on_screen(line, text, win, ray);
			line->y++;
		}
	}
}

t_pic		*new_image(t_win *win, int x, int y)
{
	t_pic *screen;

	if (!(screen = malloc(sizeof(t_pic))))
		return (NULL);
	ft_bzero(screen, sizeof(t_pic));
	if (!(screen->img = mlx_new_image(win->mlx, x, y)))
		return (NULL);
	screen->data = mlx_get_data_addr(screen->img, &screen->bpp,
				&screen->size, &screen->endian);
	screen->width = x;
	screen->height = y;
	return (screen);
}
