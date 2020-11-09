/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:10:48 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 15:17:24 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void		determine_side_draw(t_ray *ray, t_cub *cub,
										t_line *line, double wall_x)
{
	t_pic	*pic;
	int		tex_x;

	pic = cub->texture[0];
	if (ray->side == 1)
		pic = cub->texture[1];
	if (ray->side == 2)
		pic = cub->texture[2];
	if (ray->side == 3)
		pic = cub->texture[3];
	tex_x = (int)(wall_x * (double)pic->width);
	if ((ray->side == 0 || ray->side == 1) && ray->dir_x > 0)
		tex_x = pic->width - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->dir_y < 0)
		tex_x = pic->width - tex_x - 1;
	line->y0 = ray->draw_end;
	line->y1 = ray->draw_start;
	line->tex_x = tex_x;
	ver_line_texture_pic(line, cub, pic, ray);
}

void			texturisation(t_ray *ray, t_cub *cub)
{
	t_line	*line;
	double	wall_x;

	if (!(line = malloc(sizeof(t_line))))
		err_exit(2);
	ft_bzero(line, sizeof(t_line));
	line->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = cub->plr->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = cub->plr->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	if (cub->map[ray->map_x][ray->map_y] == 1)
		determine_side_draw(ray, cub, line, wall_x);
	line->y0 = 0;
	line->y1 = ray->draw_start;
	ver_line_color_pic(line, cub, cub->clr_ceilling);
	line->y0 = cub->height;
	line->y1 = ray->draw_end;
	ver_line_color_pic(line, cub, cub->clr_floor);
}
