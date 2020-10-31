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

static t_game	*init_win(void)
{
	t_game *win;

	if (!(win = malloc(sizeof(t_game))))
		return (ERR);
	ft_bzero(win, sizeof(t_game));
	if (!(win->mlx = mlx_init()))
		return (ERR);
	win->x = 400;
	win->y = 400;
	return (win);
}

//static int		init_game(int argc, char **argv, t_game *win)
//{
//    int succ;
//
//	if (!(succ = valid_input(argc, argv, win)))
//		return (ERR);
//	if (!(succ = file(argv[1], win)))
//		return (ERR);
//	if (win->save == 0)
//	{
//        if (!(win->win = mlx_new_window(win->mlx,
//                                        win->x, win->y, "Cub3D")))
//            return (invalid_file(0, win));
//        ft_putendl_fd("Starting Cub3D...", 1);
//    }
//	if (win->save == 1)
//	    ft_putendl_fd("Creating .bmp file...", 1);
//	if(!(win->screen = new_image(win)))
//		return (invalid_file(0, win));
//    if (win->save == 1)
//    {
//        if (!(succ = create_bmp(win->screen, "cub3d")))
//            return (ERR);
//    }
//    (succ) ? ft_putendl_fd("DONE!", 1) :
//                ft_putendl_fd("Smthng went wrong :/", 1);
//	return (SUCCESS);
//}

int             get_raw_data(int argc, char **argv, t_raw_game *raw_game)
{
    if (!valid_input(argc, argv, raw_game))
        return (ERR);
    if (!parse_file(argv[1], raw_game))
        return (ERR);
}

int				main(int argc, char **argv)
{
	t_game		game;
	t_raw_game  raw_game;
	int			succ;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&raw_game, sizeof(t_raw_game));
	if (!get_raw_data(argc, argv, &raw_game))
	    exit(-1);

//    game = init_win();
//	succ = init_game(argc, argv, game);
//	succ = (init_keybuff(game)) ? succ : 0;
//	if (!succ)
//		return (1);
//	mlx_hook(game->win, 2, 1L << 0, &key_pressed, game);
//	mlx_hook(game->win, 3, 1L << 1, &key_released, game);
//    mlx_hook(game->win, 17, 1L << 17, destroy_window, game);
//	mlx_loop_hook(game->mlx, loop, game);
//	if (game->save != 1)
//		mlx_loop(game->mlx);
	return (0);
}
