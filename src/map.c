/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:52:55 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:52:58 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		**tmp_map(char **map, int i, int size, t_win *win)
{
	char		**tmp;
	size_t		k;
	size_t		j;

	win->len = 0;
	win->size = size - i - 1;
	k = -1;
	j = i;
	while (map[++j])
	{
		if (win->len <= ft_strlen(map[j]))
			win->len = ft_strlen(map[j]);
	}
	if(!(tmp = ft_calloc(win->size + 1, sizeof(char *))))
		return (NULL);
	while (map[++i] && ++k < (size_t)(win->size))
	{
		if (!(tmp[k] = ft_calloc(win->len + 1, sizeof(char))))
			return (NULL);
		j = -1;
		while (map[i][++j])
			tmp[k][j] = map[i][j];
		while (j < win->len)
			tmp[k][j++] = ' ';
	}
	return (tmp);
}

static void     symbol_int(char ch, int x, int y, t_win *win)
{
    if (ch >= '0' && ch <= '2')
        win->map[x][y] = ch - '0';
    else if (ch == ' ')
        win->map[x][y] = 1;
    else if (ft_strchr("NSWE", ch))
    {
        win->map[x][y] = 0;
        win->plr->posX = (double)(x - 1) + 0.5;
        win->plr->posY = (double)y + 0.5;
    }
}

static int		map_int(char **map, t_win *win)
{
    int x1;
    int y1;
    int x;
    int y;

    x1 = -1;
    y1 = 0;
    x = 0;
    y = 0;
    if (!(win->map = ft_calloc(win->len + 1, sizeof(int *))))
		return (invalid_file(0, win));
    while ((size_t)++x1 <= win->len){
        y1 = -1;
        y = 0;
        if (!(win->map[x] = ft_calloc(win->size + 1, sizeof(int))))
			return (invalid_file(0, win));
        while ((size_t)++y1 < win->size) {
            symbol_int(map[y1][x1], x, y, win);
            y++;
        }
        x++;
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

	if (!(tmp = tmp_map(map, i - 1, size, win)))
		return (invalid_file(0, win));
	succ = check_square(tmp, win) ? 1 : 0;
	j = 0;
	plr = -1;
	while ((unsigned long)++j < win->size - 1 && succ)
	{
		k = 0;
		while ((unsigned long)++k < win->len - 1 && succ)
		{
			succ = (check_symbol(tmp, j, k, win)) ? 1 : 0;
			if (ft_strchr("NSWE", tmp[j][k]))
				plr = (set_pos(win, tmp[j][k])) ? plr + 1 : plr;
		}
	}
	succ = (!plr && map_int(tmp, win)) ? succ : 0;
	return (succ);
}
