#include "cub3d.h"

int		event_key_released(
	int key,
	void *param
)
{
	t_window	*win_infos;

	win_infos = (t_window *)param;
	if (key == TOWARD && win_infos->keybuffer->toward == 1)
		win_infos->keybuffer->toward = 0;
	else if (key == BACKWARD && win_infos->keybuffer->backward == 1)
		win_infos->keybuffer->backward = 0;
	else if (key == LEFT && win_infos->keybuffer->left == 1)
		win_infos->keybuffer->left = 0;
	else if (key == RIGHT && win_infos->keybuffer->right == 1)
		win_infos->keybuffer->right = 0;
	else if (key == CAM_LEFT && win_infos->keybuffer->turn_left == 1)
		win_infos->keybuffer->turn_left = 0;
	else if (key == CAM_RIGHT && win_infos->keybuffer->turn_right == 1)
		win_infos->keybuffer->turn_right = 0;
	bonus_event_key_released(key, win_infos);
	return (SUCCES);
}

int		event_key_pressed(
	int key,
	void *param
)
{
	t_window	*win_infos;

	win_infos = (t_window *)param;
	if (key == ESC)
		leave(0, win_infos, "");
	else if (key == TOWARD && win_infos->keybuffer->toward == 0)
		win_infos->keybuffer->toward = 1;
	else if (key == BACKWARD && win_infos->keybuffer->backward == 0)
		win_infos->keybuffer->backward = 1;
	else if (key == LEFT && win_infos->keybuffer->left == 0)
		win_infos->keybuffer->left = 1;
	else if (key == RIGHT && win_infos->keybuffer->right == 0)
		win_infos->keybuffer->right = 1;
	else if (key == CAM_LEFT && win_infos->keybuffer->turn_left == 0)
		win_infos->keybuffer->turn_left = 1;
	else if (key == CAM_RIGHT && win_infos->keybuffer->turn_right == 0)
		win_infos->keybuffer->turn_right = 1;
	bonus_event_key_pressed(key, win_infos);
	return (SUCCES);
}

static void		draw(
	t_window *win_infos
)
{
	if (!(raycasting(win_infos)))
		leave(0, win_infos, "");
	hud(win_infos);
}

int				loop_manager(
	void *param
)
{
	t_window *win_infos;

	win_infos = (t_window *)param;
	draw(win_infos);
	draw_health(win_infos);
	key_manager(win_infos);
	play_music(win_infos);
	return (SUCCES);
}

int		event_destroy_window(void *param)
{
	t_window *win_infos;

	win_infos = (t_window *)param;
	leave(0, win_infos, "");
	return (SUCCES);
}