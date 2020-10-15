#include "cub3d.h"

int		mouse_move(int x, int y, t_ident *ident)
{
	if (x < ident->player.[])
	{
		ident->player.[] += 0.05;
		ident->player.[] = x;
	}
	else if (x > ident->player.[])
	{
		ident->player.[] -= 0.05;
		ident->player.[] = x;
	}
	if (y < ident->player.[] && ident->player.[] >= 0)
	{
		ident->player.[] -= 0.02;
		ident->player.[] = y;
	}
	else if (y > ident->player.[] && ident->player.[] <= 3.14159)
	{
		ident->player.[] += 0.02;
		ident->player.[] = y;
	}
	return (0);
}

int		move_events(int keycode, t_ident *ident)
{
	if (keycode == KEY_A || keycode == KEY_LEFT)
		ident->player.posX += 20;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		ident->player.posX -= 20;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		ident->player.posY -= 20;
	if (keycode == KEY_W || keycode == KEY_UP)
		ident->player.posY += 20;
	return (0);
}

int		exit_event(void *param)
{
	param = 0;
	return (0);
}