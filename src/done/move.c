#include "cub3d.h"

static void		left(t_win *win)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = win->plr->dirX;
	oldPlaneX = win->plr->planeX;
	win->plr->dirX = win->plr->dirX
			* cos(-win->plr->rotate) - win->plr->dirY
			* sin(-win->plr->rotate);
	win->plr->dirY = oldDirX * sin(-win->plr->rotate)
			+ win->plr->dirY * cos(-win->plr->rotate);
	win->plr->planeX = win->plr->planeX
			* cos(-win->plr->rotate) - win->plr->planeY
			* sin(-win->plr->rotate);
	win->plr->planeY = oldPlaneX
			* sin(-win->plr->rotate) + win->plr->planeY
			* cos(-win->plr->rotate);
}

static void		right(t_win *win)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = win->plr->dirX;
	oldPlaneX = win->plr->planeX;
	win->plr->dirX = win->plr->dirX
			* cos(win->plr->rotate) - win->plr->dirY
			* sin(win->plr->rotate);
	win->plr->dirY = oldDirX * sin(win->plr->rotate)
			+ win->plr->dirY * cos(win->plr->rotate);
	win->plr->planeX = win->plr->planeX
			* cos(win->plr->rotate) - win->plr->planeY
			* sin(win->plr->rotate);
	win->plr->planeY = oldPlaneX
			* sin(win->plr->rotate) + win->plr->planeY
			* cos(win->plr->rotate);
}
static void		forward(t_win *win)
{
	if (win->map->map[(int)win->plr->posY]
		[(int)(win->plr->posX + win->plr->dirX
		* win->plr->speed)] == '0')
		win->plr->posX += win->plr->dirX
		* win->plr->speed;
	if (win->map->map[(int)(win->plr->posY
		+ win->plr->dirY * win->plr->speed)]
		[(int)win->plr->posX] == '0')
		win->plr->posY += win->plr->dirY
		* win->plr->speed;
}

static void		backward(t_win *win)
{
	if (win->map->map[(int)win->plr->posY]
		[(int)(win->plr->posX - win->plr->dirX
		* win->plr->speed)] == '0')
		win->plr->posX -= win->plr->dirX
		* win->plr->speed;
	if (win->map->map[(int)(win->plr->posY
		- win->plr->dirY * win->plr->speed)]
		[(int)win->plr->posX] == '0')
		win->plr->posY -= win->plr->dirY
		* win->plr->speed;
}

int 	      move_events(int key, t_win *win);
{
	if (key == A || key == _LEFT)
		left(win);
	if (key == D || key == _RIGHT)
		right(win);
	if (key == W || key == _UP)
		forward(win);
	if (key == S || key == _DOWN)
		back(win);
	return (0)
}