/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:28:25 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 14:39:07 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void		set_texture(char *path, int num, t_cub *cub)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		err_exit(7);
	close(fd);
	if (!(cub->texture[num]->img =
			mlx_xpm_file_to_image(cub->mlx, path,
			&cub->texture[num]->width,
			&cub->texture[num]->height)))
		return (err_exit(7));
	cub->texture[num]->data =
		(int *)mlx_get_data_addr(cub->texture[num]->img,
		&cub->texture[num]->bpp, &cub->texture[num]->size,
		&cub->texture[num]->endian);
}

static void		texture_format_check(char *ident, int i)
{
	while (ident[i] == ' ')
		i++;
	if (ident[i] != '.' || ident[i + 1] != '/')
		err_exit(7);
	while (ft_isprint(ident[i]) && ident[i] != ' ' && ident[i])
		i++;
	if (ident[i - 1] != 'm' || ident[i - 2] != 'p'
		|| ident[i - 3] != 'x' || ident[i - 4] != '.')
		err_exit(7);
	while (ident[i] == ' ')
		i++;
	if (ident[i])
		err_exit(7);
}

static char		*path_from_str(char *ident, int i)
{
	char	*path;
	int		size;
	int		j;
	int		k;

	size = 0;
	k = 0;
	j = i;
	path = NULL;
	while (ft_isprint(ident[i]) && ident[i] != ' ' && ident[i])
	{
		size++;
		i++;
	}
	if (!(path = ft_calloc(size + 1, sizeof(char))))
		err_exit(2);
	while (ft_isprint(ident[j]) && ident[j] != ' ' && ident[j])
		path[k++] = ident[j++];
	return (path);
}

static int		num_of_texture(char *ident, int i)
{
	int ch;

	if (ident[i] == 'S' && ident[i + 1] == 'O')
		ch = 0;
	if (ident[i] == 'N' && ident[i + 1] == 'O')
		ch = 1;
	if (ident[i] == 'W' && ident[i + 1] == 'E')
		ch = 2;
	if (ident[i] == 'E' && ident[i + 1] == 'A')
		ch = 3;
	if (ident[i] == 'S' && ident[i + 1] == ' ')
		ch = 4;
	return (ch);
}

void			texture(char *ident, t_cub *cub)
{
	char	*path;
	int		num;
	int		i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ident[i] == 'S' && ident[i + 1] == 'O')
		ft_putstr_fd("\t\t\t\tSouth texture:", 1);
	else if (ident[i] == 'N' && ident[i + 1] == 'O')
		ft_putstr_fd("\t\t\t\tNorth texture:", 1);
	else if (ident[i] == 'W' && ident[i + 1] == 'E')
		ft_putstr_fd("\t\t\t\tWest texture:", 1);
	else if (ident[i] == 'E' && ident[i + 1] == 'A')
		ft_putstr_fd("\t\t\t\tEast texture:", 1);
	else
		ft_putstr_fd("\t\t\t\tSprite texture:", 1);
	num = num_of_texture(ident, i);
	i += 2;
	while (ident[i] == ' ')
		i++;
	texture_format_check(ident, i);
	path = path_from_str(ident, i);
	set_texture(path, num, cub);
	ft_putendl_fd("\t\t\tOK", 1);
}
