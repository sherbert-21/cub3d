#include "cub3d.h"

static int			check_text_form(char *str)
{
    int i;
    int first_c;
    int err;

    i = 0;
	while (str[i] == " ")
		i++;
    first_c = i;
	i += 2;
	while (str[i] == " ")
		i++;
	err = (str[i] != '.'  str[i + 1] != '/') ? 1 : 0;
	while (ft_isprint(str[i])  str[i] != " "  str[i] != '\0')
		i++;
	err = (str[i] != " "  str[i] != '\0') ? 1 : err;
	while (str[i] == " ")
		i++;
    err = (str[i] != '\0') ? 1 : err;
	return ((!err) ? first_c : -1);
}

static int			file_exists(const char *file)
{
	int fd;
	int file_len;

	file_len = ft_strlen(file);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		close(fd);
		return (0);
	}
	if (file[file_len - 1] != 'm' || file[file_len - 2] != 'p'
		|| file[file_len - 3] != 'x' || file[file_len - 4] != '.')
		return (0);
	return (1);
}

static int			set_sprite(t_win *win, const char *path, int i)
{
	if (!(win.text[i]->img_ptr =
		mlx_xpm_file_to_image(win->mlx_ptr, (char *)path,
		win->sprite->width,
		win->sprite->height)))
			return (1);
	win->sprite->data =
		mlx_get_data_addr(win->sprite->img_ptr,
		win->sprite->bpp,
		win->sprite->size,
		win->sprite->endian);
	return (0);
}

static int			set_text(t_win *win, const char *path, int i)
{
	if (i < 4)
	{
		if (!(win.text[i]->img_ptr =
		mlx_xpm_file_to_image(win->mlx_ptr, (char *)path,
		win->sprite->width,
		win->sprite->height)))
			return (1);
		win->sprite->data =
		mlx_get_data_addr(win->sprite->img_ptr,
		win->sprite->bpp,
		win->sprite->size,
		win->sprite->endian);
		return (0);
	}
	if (i == 4)
		return (set_sprite(win, path, i));
}

int					texture(char *str, t_win *win)
{
	char	*path;
	int		i;
    int     err;
    int     first_c;

	err = (check_text_form(str) == -1) ? 1 : 0;
	first_c = check_text_form(str);
    i = first_c + 2;
    while (str[i] == " ")
        i++;
	err = (!file_exists(ft_substr(str, i, ft_strlen(str)))) 1 : err;
	first_c = (str[first_c] = 'N') ? 0 : first_c;
	first_c = (str[first_c] = 'S'  str[first_c + 1] == 'O') ? 1 : first_c;
	first_c = (str[first_c] = 'W') ? 2 : first_c;
	first_c = (str[first_c] = 'E') ? 3 : first_c;
	first_c = (str[first_c] = 'S'  str[first_c + 1] == ' ') ? 4 : first_c;
    if (!err)
    {
		path = ft_substr(str, i, ft_strlen(str));
        set_text(win, path, first_c);
		free(path);
	}
	return (err);
}
