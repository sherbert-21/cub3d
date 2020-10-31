/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:49:13 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:49:15 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_win	*init_win(void)
{
	t_win *win;

	if (!(win = malloc(sizeof(t_win))))
		return (ERR);
	ft_bzero(win, sizeof(t_win));
	if (!(win->mlx = mlx_init()))
		return (ERR);
	win->x = 400;
	win->y = 400;
	return (win);
}

static int		init_game(int argc, char **argv, t_win *win)
{
    int succ;

	if (!(succ = valid_input(argc, argv, win)))
		return (ERR);
	if (!(succ = file(argv[1], win)))
		return (ERR);
	if (win->save == 0)
	{
        if (!(win->win = mlx_new_window(win->mlx,
                                        win->x, win->y, "Cub3D")))
            return (invalid_file(0, win));
        ft_putendl_fd("Starting Cub3D...", 1);
    }
	if (win->save == 1)
	    ft_putendl_fd("Creating .bmp file...", 1);
	if(!(win->screen = new_image(win)))
		return (invalid_file(0, win));
    if (win->save == 1)
    {
        if (!(succ = create_bmp(win->screen, "cub3d")))
            return (ERR);
    }
    (succ) ? ft_putendl_fd("DONE!", 1) :
                ft_putendl_fd("Smthng went wrong :/", 1);
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_win		*win;
	int			succ;

	win = init_win();
	succ = init_game(argc, argv, win);
	succ = (init_keybuff(win)) ? succ : 0;
	if (!succ)
		return (1);
	mlx_hook(win->win, 2, 1L << 0, &key_pressed, win);
	mlx_hook(win->win, 3, 1L << 1,  &key_released, win);
//    mlx_hook(win->win, 17, 1L << 17, destroy_window, win);
	mlx_loop_hook(win->mlx, loop, win);
	if (win->save != 1)
		mlx_loop(win->mlx);
	return (0);
}
