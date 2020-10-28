#include "cub3d.h"

static void	set_camera(t_win *win, double dirX, 
							double planeX, double planeY)
{
	win->plr->dirX = dirX;
	win->plr->planeX = planeX;
	win->plr->planeY = planeY;
}

int		set_pos(t_win *win, char dir, int x, int y)
{
	if (ft_strchr("NSWE", dir) && !win->plr)
		init_plr(win);
	if (dir == 'E')
	{
		win->plr->dirY = 0.0;
		set_camera(win, 1.0, 0.0, 0.66);
	}
	else if (dir == 'W')
	{
		win->plr->dirY = 0.0;
		set_camera(win, -1.0, 0.0, -0.66);
	}
	else if (dir == 'N')
	{
		win->plr->dirY = -1.0;
		set_camera(win, 0.0, 0.66, 0.0);
	}
	else if (dir == 'S')
	{
		win->plr->dirY = 1.0;
		set_camera(win, 0.0, -0.66, 0.0);
	}
	win->plr->posX = (double)(x - 1) + 0.5;
	win->plr->posY = (double)y + 0.5;
	return ((ft_strchr("NSWE", dir)) ? SUCCESS : ERR);
}