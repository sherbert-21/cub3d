/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:50:57 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:51:06 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int invalid_ident(int err, t_win *win)
{
	if (err == 4)
		ft_putendl_fd("Invalid identifier", 1);
	else if (err == 5)
		ft_putendl_fd("Invalid resolution", 1);
	else if (err == 6)
		ft_putendl_fd("Invalid texture", 1);
	else if (err == 7)
		ft_putendl_fd("Invalid color", 1);
	else if (err == 8)
		ft_putendl_fd("Could't open the file", 1);
	else if (err == 9)
		ft_putendl_fd("Something wrong with number of identifiers", 1);
	mlx_destroy_window(win->mlx, win->win);
	exit (0);
	return (ERR);
}

int		invalid_file(int err, t_win *win)
{
	ft_putendl_fd("Error", 1);
	if (err == 0)
		ft_putendl_fd("Could't allocate mmry", 1);
	else if (err == 1)
		ft_putendl_fd("Invalid input", 1);
	else if (err == 2)
		ft_putendl_fd("No map", 1);
	else if (err == 3)
		ft_putendl_fd("Invalid map", 1);
	else if (err > 3 && err != 10)
		return(invalid_ident(err, win));
	else if (err == 10)
        ft_putendl_fd("Smthng wrong with raycasting :/", 1);
    mlx_destroy_window(win->mlx, win->win);
	exit (0);
	return (ERR);
}
