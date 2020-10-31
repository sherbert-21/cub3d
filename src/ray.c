/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:53:21 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:53:22 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_ray(t_ray *ray, t_player *plr, t_win *win)
{
	ray->cameraX = (2 * ray->pix) / (double)win->x - 1;
	ray->rayDirX = plr->dirX + plr->planeX * ray->cameraX;
	ray->rayDirY = plr->dirY + plr->planeY * ray->cameraX;
	ray->mapX = (int)plr->posX;
	ray->mapY = (int)plr->posY;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

static void		next_step(t_ray *ray, t_player *plr)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (plr->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - plr->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (plr->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - plr->posY) * ray->deltaDistY;
	}
}

static void		raycasting(t_win *win, t_ray *ray)
{
	t_player	*plr;

	plr = win->plr;
	init_values(ray, plr, win);
	next_step(ray, plr);
	hit(ray, win);
	perp_and_height(ray, plr, win);
	ray->z_buffer[ray->pix] = ray->perpWallDist;
	texturisation(ray, win);
	ray->pix++;
}

int				ray(t_win *win)
{
	t_ray		*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (ERR);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->z_buffer = malloc(sizeof(double) * win->x)))
		return (ERR);
	ft_bzero(ray->z_buffer, sizeof(double) * win->x);
	while (ray->pix < win->x)
		do_raycasting(win, ray);
	if (!draw_sprite(ray, win))
		return (ERR);
	if (win->save == 1)
		mlx_destroy_window(win->mlx, win->win);
	mlx_put_image_to_window(win->mlx, win->win,
		win->screen->img, 0, 0);
	free(ray->z_buffer);
	free(ray);
	return (SUCCESS);
}

void		perp_and_height(t_ray *ray, t_player *plr, t_win *win)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->mapx - player->posx + (1 - ray->step_x) / 2)
		/ ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->mapy - player->posy + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y;
	ray->line_height = (int)(win_infos->height / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height / 2 + ((win_infos->height / 2)
		* win_infos->player->cam_height));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2 + ((win_infos->height / 2)
		* win_infos->player->cam_height));
	if (ray->draw_end >= win_infos->height)
		ray->draw_end = win_infos->height - 1;
}

static void	predict_wall_face(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->mapx += ray->step_x;
		if (ray->step_x == 1)
			ray->side = 0;
		else if (ray->step_x == -1)
			ray->side = 1;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->mapy += ray->step_y;
		if (ray->step_y == 1)
			ray->side = 2;
		else if (ray->step_y == -1)
			ray->side = 3;
	}
}

void		hit(t_ray *ray, t_win *win)
{
	while (ray->hit == 0)
	{
		predict_wall_face(ray);
		if (win_infos->map->map[ray->mapy][ray->mapx] > '0'
			&& win_infos->map->map[ray->mapy][ray->mapx] != '2')
			ray->hit = 1;
		else if (win_infos->map->map[ray->mapy][ray->mapx] == '2')
			is_sprite(ray, win_infos);
}
