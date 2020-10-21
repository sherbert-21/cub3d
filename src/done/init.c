#include "cub3d.h"

int			init_plr(t_win *win)
{
	if (!(win->plr = malloc(sizeof(t_player))))
		return (1);
	ft_bzero(win->plr, sizeof(t_player));
	win->plr->posX = -20.0;
	win->plr->posY = -20.0;
	win->plr->speed = 0.10;
	win->plr->dirX = 1.0;
	win->plr->dirY = 0.0;
	win->plr->planeX = -20.0;
	win->plr->planeY = -20.0;
	win->plr->rotate = 0.10;
	return (0);
}

// int			init_game_keybuffer(t_win *win)
// {
// 	if (!(win->keybuffer = malloc(sizeof(t_keybuffer))))
// 		return (1);
// 	ft_bzero(win->keybuffer, sizeof(t_keybuffer));
// 	win->keybuffer->forward = 0;
// 	win->keybuffer->backward = 0;
// 	win->keybuffer->turn_left = 0;
// 	win->keybuffer->turn_right = 0;
// 	return (0);
// }

int			init_text(t_win *win,int nbr)
{
	int i;

	i = 0;
	if (!(win->text = malloc(sizeof(t_pic *) * nbr - 1)))
		return (1);
	while (i < nbr)
	{
		if (!(win->text[i] = malloc(sizeof(t_pic))))
			return (1);
		ft_bzero(win->text[i], sizeof(t_pic));
		i++;
	}
	return (0);
}

int			init_sprite(t_win *win)
{
	if (!(win->sprite = malloc(sizeof(t_pic))))
		return (1);
	ft_bzero(win->sprite, sizeof(t_pic));
	// if (!(win->sprites_on_screen = malloc(sizeof(t_list))))
	// 	return (1);
	// ft_bzero(win->sprites_on_screen, sizeof(t_list));
	// win->sprites_on_screen->x = -1;
	// win->sprites_on_screen->y = -1;
	return (0);
}