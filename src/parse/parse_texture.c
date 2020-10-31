/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:55:08 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:55:09 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			file_exists(const char *file)
{
	int fd;
	int i;

	i = ft_strlen(file) - 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		return (invalid_file(8));
	}
	if (file[i] != 'm' || file[i - 1] != 'p'
		|| file[i - 2] != 'x' || file[i - 3] != '.')
		return (invalid_file(6));
	close(fd);
	return (SUCCESS);
}

static int			set_sprite(t_game *win, const char *path)
{
    if (!(win->sprite))
            init_sprite(win);
	if (!(win->sprite->img =
		mlx_xpm_file_to_image(win->mlx, (char *)path,
		&win->sprite->width,
		&win->sprite->height)))
			return (invalid_file(6));
	win->sprite->data =
		mlx_get_data_addr(win->sprite->img,
		&win->sprite->bpp,
		&win->sprite->size,
		&win->sprite->endian);
	return (SUCCESS);
}

static int			set_text(t_game *win, const char *path, int c)
{
	if (c < 4)
	{
		win->text[c]->data =
			mlx_get_data_addr(win->text[c]->img,
			&win->text[c]->bpp,
			&win->text[c]->size,
			&win->text[c]->endian);
	}
	else
		return (set_sprite(win, path));
	return (SUCCESS);
}

//int					parse_texture(char *path, t_texture *texture, void *mlx)
//{
//    int     i;
//	int		k;
//
//	if (!(file_exists(path)))
//		return (ERR);
//    if (!(texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height)))
//        return (invalid_file(6));
//	return (i);
//}
