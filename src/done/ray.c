#include "cub3d.h"

static void		init_ray(t_ray *ray, t_plr *plr, t_win *win)
{
	ray->cameraX = (2 * ray->pix) / (double)win->x - 1;
	ray->rayDirX = plr->DirX + plr->planeX * ray->cameraX;
	ray->rayDirY = plr->dirY + plr->planeY * ray->cameraX;
	ray->mapX = (int)plr->posX;
	ray->mapY = (int)plr->posY;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

static void		next_step(t_ray *ray, t_plr *plr)
{
	if (ray->ray_DirX < 0)
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
	t_plr	*plr;

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
		return (1);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->z_buffer = malloc(sizeof(double) * win->x)))
		return (1);
	ft_bzero(ray->z_buffer, sizeof(double) * win->x);
	while (ray->pix < win->x)
		do_raycasting(win, ray);
	if (!draw_sprite(ray, win))
		return (1);
	if (win->save == 1)
	{
		win->save = 0;
		create_bitmap(win->save, "cub3D");
		leave(0, win, "");
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
		win->save->img_ptr, 0, 0);
	free(ray->z_buffer);
	free(ray);
	return (0);
}

void		perp_and_height(t_ray *ray, t_plr *plr, t_win *win)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perpWallDist = (ray->mapX - plr->posX + (1 - ray->stepX) / 2)
		/ ray->ray_DirX;
	else
		ray->perpWallDist = (ray->mapY - plr->posY + (1 - ray->stepY) / 2)
		/ ray->rayDirY;
	ray->line_height = (int)(win->y / ray->perpWallDist);
	ray->draw_start = (-ray->line_height / 2 + ((win->y / 2)
		* win->plr->cam_height));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2 + ((win->y / 2)
		* win->plr->cam_height));
	if (ray->draw_end >= win->y)
		ray->draw_end = win->y - 1;
}

static void	predict_wall_face(t_ray *ray)
{
	if (ray->sideDistX < ray->sideDistY)
	{
		ray->sideDistX += ray->deltaDistX;
		ray->mapX += ray->stepX;
		if (ray->stepX == 1)
			ray->side = 0;
		else if (ray->stepX == -1)
			ray->side = 1;
	}
	else
	{
		ray->sideDistY += ray->deltaDistY;
		ray->mapY += ray->stepY;
		if (ray->stepY == 1)
			ray->side = 2;
		else if (ray->stepY == -1)
			ray->side = 3;
	}
}

void		hit(t_ray *ray, t_win *win)
{
	while (ray->hit == 0)
	{
		predict_wall_face(ray);
		if (win->map[ray->mapY][ray->mapX] > '0'
			&& win-->map[ray->mapY][ray->mapX] != '2')
			ray->hit = 1;
		else if (win->map[ray->mapY][ray->mapX] == '2')
			is_sprite(ray, win);
	}
}
