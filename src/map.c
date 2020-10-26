#include "cub3d.h"

static char		**tmp_map(char **map, int i, int size, t_win *win)
{
	char		**tmp;
	size_t		k;
	size_t		j;

	win->len = 0;
	k = 0;
	j = i;
	while (map[++j])
	{
		if (win->len <= ft_strlen(map[j]))
			win->len = ft_strlen(map[j]);
	}
	tmp = ft_calloc(size - i + 1, sizeof(char *));
	while (map[++i])
	{
		j = -1;
		tmp[k] = ft_calloc(win->len + 1, sizeof(char));
		while (map[i][++j])
			tmp[k][j] = map[i][j];
		while (j < win->len)
			tmp[k][j++] = ' ';
		k++;
	}
	return (tmp);
}

static int		check_square(char **tmp, int i, int size)
{
	int		j;
	int		k;
	int		err;

	j = -1;
	err = 0;
	k = -1;
	while (++j <= size - i - 1 && !err)
		err = (ft_strchr(" 1", tmp[j][0])) ? 1 : err;
	while (tmp[j - 1][++k] && !err)
		err = (ft_strchr(" 1", tmp[j - 1][k])) ? 1 : err;
	while (--j >= 0 && !err)
		err = (ft_strchr(" 1", tmp[j][k - 1])) ? 1 : err;
	while (--k >= 0 && !err)
		err = (ft_strchr(" 1", tmp[j + 1][k])) ? 1 : err;
	return (err);
}

static int		check_symbol(char **tmp, int j, int k)
{
	if (ft_strchr(" 012NSWE", tmp[j + 1][k]))
		return (SUCK);
	if (tmp[j][k] == 32)
	{
		if (ft_strchr(" 1", tmp[j + 1][k]) ||
			ft_strchr(" 1", tmp[j - 1][k]) ||
			ft_strchr(" 1", tmp[j][k + 1]) ||
			ft_strchr(" 1", tmp[j][k - 1]))
			return (SUCK);
	}
	return (ERR);
}

static int		map_int(char **map, int i, int size, t_win *win)
{
	int j;
	int k;
	int err;

	k = -1;
	err = (!(win->map = ft_calloc(size - i + 1, sizeof(int *)))) ? 1 : 0;
	while (map[++k] && !err)
	{
		j = -1;
		if (!(win->map[k] = ft_calloc(win->len, sizeof(int))))
			err = 1;
		while (map[k][++j] && !err)
		{
			if (map[k][j] >= '0' && map[k][j] <= '2')
				win->map[k][j] = map[k][j] - '0';
			if (map[k][j] == ' ')
				win->map[k][j] = 1;
			if (ft_strchr("NSWE", map[k][j]))
				win->map[k][j] = (int)map[k][j];
		}
	}
	return (err);
}

int				map_parce(char **map, int i, int size, t_win *win)
{
	char	**tmp;
	int		err;
	int		j;
	size_t	k;
	int		player;

	tmp = tmp_map(map, i - 1, size, win);
	err = check_square(tmp, i, size);
	j = 0;
	player = 0;
	while (++j < (win->size = size - i) - 1 && !err)
	{
		k = 0;
		while (++k < ft_strlen(tmp[j]) - 1 && !err)
		{
			err = (check_symbol(tmp, j, k) == 1) ? 1 : err;
			player = (set_pos(win, tmp[j][k], j, k)) ? player + 1 : player;
		}
	}
	err = (player != 1) ? 1 : err;
	err = (!err && map_int(tmp, i - 1, size, win)) ? 1 : err;
	return (err);
}