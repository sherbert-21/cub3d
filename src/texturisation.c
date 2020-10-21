static void	determine_side_draw(
	t_ray *ray,
	t_win *win,
	t_str *str,
	double wall_x
)
{
	t_image	*img;
	int		tex_x;

	img = win->texts[3];
	if (ray->side == 1)
		img = win->texts[2];
	if (ray->side == 2)
		img = win->texts[1];
	if (ray->side == 3)
		img = win->texts[0];
	tex_x = (int)(wall_x * (double)img->width);
	if ((ray->side == 0 || ray->side == 1) && ray->ray_dir_x > 0)
		tex_x = img->width - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->ray_dir_y < 0)
		tex_x = img->width - tex_x - 1;
	str->y0 = ray->draw_end;
	str->y1 = ray->draw_start;
	str->tex_x = tex_x;
	ver_str_text_image(str, win, img, ray);
}

void		texturisation(
	t_ray *ray,
	t_win *win
)
{
	t_image	*img;
	t_str	*str;
	double	wall_x;

	if (!(str = malloc(sizeof(t_str))))
		leave(1, win, "Error\nDuring str malloc\n");
	ft_bzero(str, sizeof(t_str));
	str->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = win->player->posy + ray->perpWallDist * ray->ray_dir_y;
	else
		wall_x = win->player->posx + ray->perpWallDist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	if (win->map->map[ray->mapy][ray->mapx] == '1')
		determine_side_draw(ray, win, str, wall_x);
	str->y0 = 0;
	str->y1 = ray->draw_start;
	ver_str_color_image(str, win, win->color_ceiling);
	str->y0 = win->height;
	str->y1 = ray->draw_end;
	ver_str_color_image(str, win, win->color_floor);
}