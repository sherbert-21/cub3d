#include "cub3d.h"

static int			check_text_form(char *str)
{
    int i;
    int succ;

    i = 0;
	while (str[i] == ' ')
		i++;
	i += 2;
	while (str[i] == ' ')
		i++;
	succ = (str[i] != '.' || str[i + 1] != '/') ? 0 : 1;
	while (ft_isprint(str[i]) && str[i] != ' ' && str[i])
		i++;
	succ = (str[i] == ' ' || str[i] == '\0') ? succ : 0;
	while (str[i] == ' ')
		i++;
    succ = (str[i] == '\0') ? succ : 0;
	return (succ);
}

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

static int			set_text(t_win *win, const char *path, int c)
{
	if (!win->text)
		init_text(win, 5);
	c = (path[c] == 'N') ? 0 : c;
	c = (path[c] == 'S' && path[c + 1] == 'O') ? 1 : c;
	c = (path[c] == 'W') ? 2 : c;
	c = (path[c] == 'E') ? 3 : c;
	c = (path[c] == 'S' && path[c + 1] == ' ') ? 4 : c;
	if (c < 4)
	{
		if (!(win->text[c]->img =
			mlx_xpm_file_to_image(win->mlx, (char *)path,
			&win->text[c]->width,
			&win->text[c]->height)))
			return (invalid_file(6));
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

int					texture(char *str, int first_c, t_win *win)
{
	char	*path;
    int     i;
	int		k;

	if (!(check_text_form(str)))
		return (invalid_file(6));
    i = first_c + 2;
    while (str[i] == ' ')
        i++;
	k = i;
	while (str[k] != ' ')
		k++;
	path = ft_substr(str, i, k - i);
	if (!(file_exists(path)))
	{
		save_free(&path);
		return (ERR);
	}
    i = set_text(win, path, first_c);
	save_free(&path);
	return (i);
}
