/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:10:13 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 15:32:53 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void		next_step(t_ray *ray, t_player *plr)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (plr->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - plr->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (plr->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - plr->pos_y) * ray->delta_dist_y;
	}
}

static void		init_values(t_ray *ray, t_player *plr, t_cub *cub)
{
	ray->camera_x = (2 * ray->pix) / (double)cub->width - 1;
	ray->dir_x = plr->dir_x + plr->plane_x * ray->camera_x;
	ray->dir_y = plr->dir_y + plr->plane_y * ray->camera_x;
	ray->map_x = (int)plr->pos_x;
	ray->map_y = (int)plr->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

static void		raycasting(t_cub *cub, t_ray *ray)
{
	t_player	*plr;

	plr = cub->plr;
	ray->pix = 0;
	while (ray->pix < cub->screen->width)
	{
		init_values(ray, plr, cub);
		next_step(ray, plr);
		hit(ray, cub);
		perp_and_height(ray, plr, cub);
		ray->z_buff[ray->pix] = ray->perp_wall_dist;
		texturisation(ray, cub);
		ray->pix++;
	}
}

int				ray(t_cub *cub)
{
	t_ray		*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		err_exit(2);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->z_buff = malloc(sizeof(double) * cub->width)))
		err_exit(2);
	ft_bzero(ray->z_buff, sizeof(double) * cub->width);
	raycasting(cub, ray);
	draw_sprite(ray, cub);
	if (cub->save_bmp == 1)
	{
		create_bitmap(cub->screen, "cub3D.bmp");
		return (SUCCESS);
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->screen->img, 0, 0);
	free(ray->z_buff);
	free(ray);
	return (SUCCESS);
}
