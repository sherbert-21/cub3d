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
	if(!(tmp = ft_calloc(size - i + 1, sizeof(char *))))
		return (NULL);
	while (map[++i])
	{
		j = ft_strlen(map[i]);
		if (!(tmp[k] = ft_strdup(map[i])))
			return (NULL);
		while (j < win->len)
			tmp[k][j++] = ' ';
		k++;
	}
	return (tmp);
}

static int		check_square(char **tmp, int i, int size, int len)
{
	int		j;
	int		k;
	int		succ;

	j = -1;
	succ = 1;
	k = -1;
	while (++j < size - i - 1 && succ)
		succ = (ft_strchr(" 1", tmp[j][0])) ? 0 : succ;
	while (++k < len - 1 && succ)
		succ = (ft_strchr(" 1", tmp[j - 1][k])) ? 0 : succ;
	while (--j >= 0 && succ)
		succ = (ft_strchr(" 1", tmp[j][k - 1])) ? 0 : succ;
	while (--k >= 0 && succ)
		succ = (ft_strchr(" 1", tmp[j + 1][k])) ? 0 : succ;
	return (succ);
}

static int		check_symbol(char **tmp, int j, int k)
{
	if (tmp[j][k] == ' ')
	{
		if (ft_strchr(" 1", tmp[j + 1][k]) ||
			ft_strchr(" 1", tmp[j - 1][k]) ||
			ft_strchr(" 1", tmp[j][k + 1]) ||
			ft_strchr(" 1", tmp[j][k - 1]))
			return (SUCCESS);
	}
	else if (ft_strchr("012NSWE", tmp[j][k]))
		return (SUCCESS);
	return (invalid_file(3));
}

static int		map_int(char **map, int i, int size, t_win *win)
{
	int j;
	int k;

	k = -1;
	if (!(win->map = ft_calloc(size - i + 1, sizeof(int *))))
		return (invalid_file(0));
	while (map[++k])
	{
		j = -1;
		if (!(win->map[k] = ft_calloc(win->len, sizeof(int))))
			return (invalid_file(0));
		while (map[k][++j])
		{
			if (map[k][j] >= '0' && map[k][j] <= '2')
				win->map[k][j] = map[k][j] - '0';
			if (map[k][j] == ' ')
				win->map[k][j] = 1;
			if (ft_strchr("NSWE", map[k][j]))
				win->map[k][j] = (int)map[k][j];
		}
	}
	return (SUCCESS);
}

int				map_parce(char **map, int i, int size, t_win *win)
{
	char	**tmp;
	int		succ;
	int		j;
	size_t	k;
	int		plr;

	win->size = size - i;
	ft_putnbr_fd(win->size, 1);
	if (!(tmp = tmp_map(map, i - 1, size, win)))
		return (invalid_file(0));
	succ = check_square(tmp, i, size, win->len) ? 1 : 0;
	j = 0;
	plr = -1;
	while (tmp[++j] && succ)
	{
		k = 0;
		while (tmp[j][++k] && succ)
		{

			succ = (check_symbol(tmp, j, k) != 1) ? 0 : 1;
			if (ft_strchr("NSWE", tmp[j][k]))
			{
				printf("aaa\n");
				plr = (set_pos(win, tmp[j][k], j, k)) ? plr + 1 : plr;
			}
		}
	}
	for (int q = 0; tmp[q]; q++)
	    ft_putstr_fd(tmp[q] , 1);
	printf("%d\n", plr);
	succ = (succ && !plr && map_int(tmp, i - 1, size, win)) ? 0 : succ;
	return (succ);
}