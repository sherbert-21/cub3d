#include "cub3d.h"

static int			check_text_form(char *str)
{
    int i;
    int first_c;
    int err;

    i = 0;
	while (str[i] == ' ')
		i++;
    first_c = i;
	i += 2;
	while (str[i] == ' ')
		i++;
	err = (str[i] != '.' || str[i + 1] != '/') ? 0 : 1;
	while (ft_isprint(str[i]) && str[i] != ' ' && str[i])
		i++;
	err = (str[i] != ' ' || str[i] != '\0') ? 0 : err;
	while (str[i] == ' ')
		i++;
    err = (str[i] != '\0') ? 0 : err;
	return (err);
}

static int			file_exists(const char *file)
{
	int fd;
	int file_len;

	file_len = ft_strlen(file);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		return (ERR);
	}
	if (file[file_len - 1] != 'm' || file[file_len - 2] != 'p'
		|| file[file_len - 3] != 'x' || file[file_len - 4] != '.')
		return (ERR);
	return (SUCCESS);
}

static int			set_sprite(t_win *win, const char *path)
{
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

static int			set_text(t_win *win, const char *path, int i)
{
	if (i < 4)
	{
		if (!(win->text[i]->img =
			mlx_xpm_file_to_image(win->mlx, (char *)path,
			&win->text[i]->width,
			&win->text[i]->height)))
			return (invalid_file(6));
		win->text[i]->data =
			mlx_get_data_addr(win->text[i]->img,
			&win->text[i]->bpp,
			&win->text[i]->size,
			&win->text[i]->endian);
	}
	else
		return (set_sprite(win, path));
	return (SUCCESS);
}

int					texture(char *str, t_win *win)
{
	char	*path;
    int     i;
    int     first_c;

	if (!(first_c = check_text_form(str)))
		return (invalid_file(6));
    i = first_c + 2;
    while (str[i] == ' ')
        i++;
	path = ft_substr(str, i, ft_strlen(str));
	if (!(file_exists(path)))
	{
		free(path);
		return (invalid_file(6));
	}
	first_c = (str[first_c] = 'N') ? 0 : first_c;
	first_c = (str[first_c] = 'S' && str[first_c + 1] == 'O') ? 1 : first_c;
	first_c = (str[first_c] = 'W') ? 2 : first_c;
	first_c = (str[first_c] = 'E') ? 3 : first_c;
	first_c = (str[first_c] = 'S' && str[first_c + 1] == ' ') ? 4 : first_c;
    i = set_text(win, path, first_c);
	free(path);
	return (i);
}
