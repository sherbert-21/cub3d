#include "cub3d.h"

static int		valid_identifier(char *ident)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ft_strchr("RSF", ident[i]) && ident[i + 1] == ' ')
		return (0);
	else if (ft_strchr("SN", ident[i]) && ident[i + 1] == 'O')
		return (0);
	else if (ident[i] == 'W' && ident[i + 1] == 'E')
		return (0);
	else if (ident[i] == 'E' && ident[i + 1] == 'A')
		return (0);
	else
		return (1);
}

static int		identifier_parce(char *ident, t_win *win)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ident[i] == 'R')
		return (resolution(++ident, win));
	else if (ident[i] == 'F' || ident[i] == 'C')
		return (color(ident, ident[i], i, win));
	else
		return (texture(ident, win));
}

static int		file_parce(char **map, t_win *win, int size)
{
	int i;
	int err;

	i = 0;
	err = 0;
	while (map[i] && map[i][0] != ' ' && !err && map[i][0] != '1')
	{
		while (map[i][0] == '\n')
			i++;
		if (!(err = valid_identifier(map[i])))
			identifier_parce(map[i++], win);
		if (err)
			invalid_file(3);
	}
	if (!err && map_parce(map, i, size, win))
		invalid_file(4);
	return (err || map_parce(map, i, size, win));
}

static int		lst_to_str(t_list *file_lst, int size, t_win *win)
{
	char	**file;
	int		i;
	int 	k;
	int		err;

	i = 0;
	file = ft_calloc(size + 1, sizeof(char *));
	err = (!file) ? 1 : 0;
	while (!err && file_lst)
	{
		if (!(file[i] = ft_calloc(ft_strlen(file_lst->content), sizeof(char))))
			err = 1;
		file[i++] = file_lst->content;
		file_lst = file_lst->next;
	}
	err = (file_parce(file, win, size)) ? 1 : err;
	return (err);
}

int				file(int argc, char **argv, t_win *win)
{
	int		fd;
	t_list	*file_lst;
	char	*line;
	int		err;

	file_lst = NULL;
	err = valid_input(argc, argv, win);
	if (err)
		invalid_file(err);
	if (!err)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line))
			ft_lstadd_back(&file_lst, ft_lstnew(line));
		ft_lstadd_back(&file_lst, ft_lstnew(line));
		err = ((lst_to_str(file_lst, ft_lstsize(file_lst), win))) ? 1 : err;
		win->plr->planeX = 0.0;
		win->plr->planeY = 0.66;
	}
	return (err);
}
