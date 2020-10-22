#include "cub3d.h"

static void	side_draw(t_ray *ray, t_win *win, 
								t_line *line, double wall_x)
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
	line->y0 = ray->draw_end;
	line->y1 = ray->draw_start;
	line->texX = texX;
	ver_line_text_pic(line, win, text, ray);
}

void		texturisation(t_ray *ray, t_win *win)
{
	t_pic	*text;
	t_line	*line;
	double	wall_x;

	if (!(line = malloc(sizeof(t_line))))
		return (1);
	ft_bzero(line, sizeof(t_line));
	line->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wall_x = win->player->posy + ray->perpWallDist * ray->rayDirY;
	else
		wall_x = win->player->posx + ray->perpWallDist * ray->rayDirX;
	wall_x -= floor(wall_x);
	if (win->map->map[ray->mapy][ray->mapx] == '1')
		side_draw(ray, win, line, wall_x);
	line->y0 = 0;
	line->y1 = ray->draw_start;
	ver_line_color_image(line, win, win->color_ceiling);
	line->y0 = win->y;
	line->y1 = ray->draw_end;
	ver_line_color_image(line, win, win->color_floor);
}
