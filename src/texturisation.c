static void	determine_side_draw(t_ray *ray, t_win *win, t_str *str, double wall_x)
{
	t_pic	*text;
	int		texX;

	text = win->text[3];
	if (ray->side == 1)
		text = win->text[2];
	if (ray->side == 2)
		text = win->text[1];
	if (ray->side == 3)
		text = win->text[0];
	texX = (int)(wall_x * (double)text->width);
	if ((ray->side == 0 || ray->side == 1) && ray->rayDirX > 0)
		texX = text->width - texX - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->rayDirY < 0)
		texX = text->width - texX - 1;
	str->y0 = ray->draw_end;
	str->y1 = ray->draw_start;
	str->texX = texX;
	ver_str_text_pic(str, win, text, ray);
}

void		texturisation(t_ray *ray, t_win *win)
{
	t_pic	*text;
	t_str	*str;
	double	wall_x;

	if (!(str = malloc(sizeof(t_str))))
		leave(1, win, "Error\nDuring str malloc\n");
	ft_bzero(str, sizeof(t_str));
	str->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = win->player->posy + ray->perpWallDist * ray->rayDirY;
	else
		wall_x = win->player->posx + ray->perpWallDist * ray->rayDirX;
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