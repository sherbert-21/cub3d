#include "cub3d.h"

int		mouse_move(int x, int y, t_img *img)
{
	if (x < img->mouse_x)
	{
		img->angle_z += 0.05;
		img->mouse_x = x;
	}
	else if (x > img->mouse_x)
	{
		img->angle_z -= 0.05;
		img->mouse_x = x;
	}
	if (y < img->mouse_y && img->angle_x >= 0)
	{
		img->angle_x -= 0.02;
		img->mouse_y = y;
	}
	else if (y > img->mouse_y && img->angle_x <= 3.14159)
	{
		img->angle_x += 0.02;
		img->mouse_y = y;
	}
	return (0);
}

int		move_events(int keycode, t_img *img)
{
	if (keycode == KEY_A || keycode == KEY_LEFT)
		img->center_x += 20;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		img->center_x -= 20;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		img->center_z -= 20;
	if (keycode == KEY_W || keycode == KEY_UP)
		img->center_z += 20;
	return (0);
}

int		exit_event(void *param)
{
	param = 0;
	return (0);
}