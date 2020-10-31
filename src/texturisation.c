/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:55:18 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:55:19 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	determine_side_draw(t_ray *ray, t_win *win, 
								t_line *line, double wallX)
{
	t_pic	*img;
	int		texX;

	img = win->text[3];
	if (ray->side == 1)
		img = win->text[2];
	if (ray->side == 2)
		img = win->text[1];
	if (ray->side == 3)
		img = win->text[0];
	texX = (int)(wallX * (double)img->width);
	if ((ray->side == 0 || ray->side == 1) && ray->rayDirX > 0)
		texX = img->width - texX - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->rayDirY < 0)
		texX = img->width - texX - 1;
	line->y0 = ray->drawEnd;
	line->y1 = ray->drawStart;
	line->texX = texX;
	ver_line_text_pic(line, win, img, ray);
}

void		texturisation(t_ray *ray, t_win *win)
{
	t_line	*line;
	double	wallX;

	if (!(line = malloc(sizeof(t_line))))
		exit (invalid_file(0, win));
	ft_bzero(line, sizeof(t_line));
	line->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wallX = win->plr->posY + ray->perpWallDist * ray->rayDirY;
	else
		wallX = win->plr->posX + ray->perpWallDist * ray->rayDirX;
	wallX -= floor(wallX);
	if (win->map[ray->mapX][ray->mapY] == 1)
		determine_side_draw(ray, win, line, wallX);
	line->y0 = 0;
	line->y1 = ray->drawStart;
	ver_line_clr_image(line, win, win->clr_c);
	line->y0 = win->y;
	line->y1 = ray->drawEnd;
	ver_line_clr_image(line, win, win->clr_f);
}
