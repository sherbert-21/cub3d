#include "cub3d.h"

static void		next_step(
	t_ray *ray,
	t_player *player
)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->posx - ray->mapx) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->mapx + 1.0 - player->posx) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->posy - ray->mapy) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->mapy + 1.0 - player->posy) * ray->delta_dist_y;
	}
}

static void		init_values(
	t_ray *ray,
	t_player *player,
	t_window *win_infos
)
{
	ray->camera_x = (2 * ray->pix) / (double)win_infos->width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->mapx = (int)player->posx;
	ray->mapy = (int)player->posy;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void		do_raycasting(
	t_window *win_infos,
	t_ray *ray
)
{
	t_player	*player;

	player = win_infos->player;
	init_values(ray, player, win_infos);
	next_step(ray, player);
	hit(ray, win_infos);
	perp_and_height(ray, player, win_infos);
	ray->z_buffer[ray->pix] = ray->perp_wall_dist;
	texturisation(ray, win_infos);
	ray->pix++;
}

int				raycasting(
	t_window *win_infos
)
{
	t_ray		*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (ERROR);
	ft_bzero(ray, sizeof(t_ray));
	if (!(ray->z_buffer = malloc(sizeof(double) * win_infos->width)))
		return (ERROR);
	ft_bzero(ray->z_buffer, sizeof(double) * win_infos->width);
	while (ray->pix < win_infos->width)
		do_raycasting(win_infos, ray);
	if (!draw_sprite(ray, win_infos))
		return (ERROR);
	if (win_infos->save == 1)
	{
		win_infos->save = 0;
		create_bitmap(win_infos->img, "cub3D");
		leave(0, win_infos, "");
	}
	mlx_put_image_to_window(win_infos->mlx_ptr, win_infos->win_ptr,
		win_infos->img->img_ptr, 0, 0);
	free(ray->z_buffer);
	free(ray);
	return (SUCCES);
}

void		perp_and_height(
	t_ray *ray,
	t_player *player,
	t_window *win_infos
)
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

static void	predict_wall_face(
	t_ray *ray
)
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

void		hit(
	t_ray *ray,
	t_window *win_infos
)
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
}
