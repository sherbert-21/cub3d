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

static int		init(t_game *game, t_raw_game *raw_game)
{
	if (!(game->mlx = mlx_init()))
		return (ERR);
	if (!init_from_raw(game, raw_game))
		return (ERR);
	if (!(game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D")))
		return (invalid_file(0));
	if(!(game->screen = new_image(game)))
		return (invalid_file(0));
	return (SUCCESS);
}

int             get_raw_data(int argc, char **argv, t_raw_game *raw_game)
{
    if (!valid_input(argc, argv, raw_game))
        return (ERR);
    if (!parse_file(argv[1], raw_game))
        return (ERR);
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_game		game;
	t_raw_game  raw_game;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&raw_game, sizeof(t_raw_game));
	if (!get_raw_data(argc, argv, &raw_game))
	    exit(-1);
	if (!init(&game, &raw_game))
		exit(-1);
//	if (game->need_save_first_frame == 1)
//	{
//		if (!(succ = create_bmp(game->screen, "cub3d")))
//			return (ERR);
//	}
//	succ = (init_keybuff(game)) ? succ : 0;
//	mlx_hook(game->win, 2, 1L << 0, &key_pressed, game);
//	mlx_hook(game->win, 3, 1L << 1, &key_released, game);
//  mlx_hook(game->win, 17, 1L << 17, destroy_window, game);
//	mlx_loop_hook(game->mlx, render, game);
//	mlx_loop(game->mlx);
	return (0);
}
