#include "cub3d.h"

static char		**tmp_map(char **map, int i, int size)
{
	int		len;
	char	**tmp;
	int		k;
	int		j;

	len = 0;
	k = 0;
	j = i;
	while (map[++j])
		len = (len < ft_strlen(map[j])) ? ft_strlen(map[j]) : len;
	tmp = ft_calloc(size - i + 1, sizeof(char *));
	while (map[++i])
	{
		j = -1;
		tmp[k] = ft_calloc(len + 1, sizeof(char));
		while (map[i][++j])
			tmp[k][j] = map[i][j];
		while (j < len)
			tmp[k][j++] = ' ';
		k++;
	}
	return (tmp);
}

static int		check_square(char **tmp)
{
	int		j;
	int		k;
	int		err;

	j = -1;
	k = -1;
	err = 0;
	while (tmp[++j])
		err = (*tmp[j] != 32 || *tmp[j] != 49) ? 1 : err;
	while (tmp[j - 1][++k])
		err = (tmp[j - 1][k] != 32 || tmp[j - 1][k] != 49) ? 1 : err;
	while (--j >= 0)
		err = (tmp[j][k - 1] != 32 || tmp[j][k - 1] != 49) ? 1 : err;
	while (--k >= 0)
		err = (tmp[j + 1][k] != 32 || tmp[j + 1][k] != 49) ? 1 : err;
	return (err);
}

 static int		check_symbol(char **tmp, int j, int k)
{
	if (!ft_strchr(" 012NSWE", tmp[j + 1][k]))
		return (1);
	if (tmp[j][k] == 32)
	{
		if (!ft_strchr(" 1", tmp[j + 1][k]) ||
			!ft_strchr(" 1", tmp[j - 1][k]) ||
			!ft_strchr(" 1", tmp[j][k + 1]) ||
			!ft_strchr(" 1", tmp[j][k - 1]))
			return (1);
	}
	return (0);
}

int				check_map(char **map, int i, int size)
{
	char	**tmp;
	int		err;
	int		j;
	int		k;
	int		player;

	tmp = tmp_map(map, i - 1, size);
	err = check_square(tmp);
	j = i;
	player = 0;
	while (++j < size - 1 && !err)
	{
		k = 0;
		while (++k < ft_strlen(tmp[j]) - 1 && !err)
		{
			err = (check_symbol == 1) ? 1 : err;
			player = (ft_strchr("NSWE", tmp[j][k])) ? player + 1 : player;
		}
	}
	err = (player != 1) ? 1 : err;
	save_free_map(&tmp);
	return (err);
}

int				valid_input(int argc, char **argv)
{
	if (argc > 3 || argc == 1)
		return (1);
	else
	{
		if (argc == 1)
		{
			if (ft_strnstr(argv[1], "--save", ft_strlen("--save")))
				return (2);
			else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
				return (1);
		}
		if (argc == 2)
		{
			if (ft_strnstr(argv[1], "--save", ft_strlen("--save")))
				return (1);
			else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
				return (1);
		}
	}
	return (0);
}
