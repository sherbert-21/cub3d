/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:16:45 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 16:17:19 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static t_cub	*init_cub(void)
{
	t_cub *cub;

	if (!(cub = malloc(sizeof(t_cub))))
		err_exit(2);
	ft_bzero(cub, sizeof(t_cub));
	if (!(cub->mlx = mlx_init()))
		return (ERR);
	cub->width = 400;
	cub->height = 0;
	cub->clr_ceilling = 0;
	cub->clr_floor = 0;
	cub->map_x = 0;
	cub->map_y = 0;
	cub->save_bmp = 0;
	return (cub);
}

int				main(int argc, char **argv)
{
	t_cub *cub;

	cub = init_cub();
	init_texture(cub, 5);
	init_plr(cub);
	init_game_sprite(cub);
	init_game_keybuffer(cub);
	file_parce(argc, argv, cub);
	cub->screen = new_pic(cub, cub->width, cub->height);
	if (cub->save_bmp == 1)
		ray(cub);
	if (cub->save_bmp == 0)
	{
		if (!(cub->win = mlx_new_window(cub->mlx,
			cub->width, cub->height, "Cub3D")))
			err_exit(2);
		mlx_hook(cub->win, 2, 1L << 0, key_pressed, cub);
		mlx_hook(cub->win, 3, 1L << 1, key_released, cub);
		mlx_hook(cub->win, 17, 1L << 17, event_destroy_window, cub);
		mlx_loop_hook(cub->mlx, loop, cub);
		mlx_loop(cub->mlx);
	}
	return (0);
}
