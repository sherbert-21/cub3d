#include "cub3d.h"

static void	side_draw(t_ray *ray, t_win *win, 
								t_line *line, double wallX)
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
	texX = (int)(wallX * (double)text->width);
	if ((ray->side == 0 || ray->side == 1) && ray->rayDirX > 0)
		texX = text->width - texX - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->rayDirY < 0)
		texX = text->width - texX - 1;
	line->y0 = ray->drawEnd;
	line->y1 = ray->drawStart;
	line->texX = texX;
	ver_line_text_pic(line, win, text, ray);
}

void		texturisation(t_ray *ray, t_win *win)
{
	t_line	*line;
	double	wallX;

	if (!(line = malloc(sizeof(t_line))))
	ft_bzero(line, sizeof(t_line));
	line->x = ray->pix;
	if (ray->side == 0 || ray->side == 1)
		wallX = win->plr->posY + ray->perpWallDist * ray->rayDirY;
	else
		wallX = win->plr->posX + ray->perpWallDist * ray->rayDirX;
	wallX -= floor(wallX);
	if (win->map[ray->mapY][ray->mapX] == '1')
		side_draw(ray, win, line, wallX);
	line->y0 = 0;
	line->y1 = ray->drawStart;
	ver_line_clr_image(line, win, win->clr_c);
	line->y0 = win->y;
	line->y1 = ray->drawEnd;
	ver_line_clr_image(line, win, win->clr_f);
}
