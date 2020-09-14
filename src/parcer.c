#include "cub3d.h"
#include <stdio.h>

// err_1 - invalid_input
// err_2 - no_map
// err_3 - invalid_ident
// err_4 - invalid_map
// err_5 - couldn't allocate

// void			save_free_map(char ***str)
// {
// 	int i;

// 	i = -1;
// 	while (str[++i])
// 		save_free(str[i]);
// }

static void		invalid_map(int err)
{
	ft_putendl_fd("Error", 1);
	if (err == 1)
		ft_putendl_fd("Invalid input", 1);
	else if (err == 2)
		ft_putendl_fd("No map", 1);
	else if (err == 3)
		ft_putendl_fd("Invalid identifier or information for object", 1);
	else if (err == 4)
		ft_putendl_fd("Invalid map", 1);
	else if (err == 5)
		ft_putendl_fd("Could't allocate mmry", 1);
}

static int		parcer(char **map, t_ident *ident, int size)
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
			identifier(map[i++], ident);
		if (err)
			invalid_map(3);
	}
	if (!err && check_map(map, i, size, ident))
		invalid_map(4);
	return (err || check_map(map, i, size, ident));
}

static int		map_parcer(t_list *map_lst, int size, t_ident *ident)
{
	char	**map;
	int		i;
	int k;
	int		err;

	i = 0;
	map = ft_calloc(size + 1, sizeof(char *));
	err = (!map) ? 1 : 0;
	while (!err && map_lst)
	{
		if (!(map[i] = ft_calloc(ft_strlen(map_lst->content), sizeof(char))))
			err = 1;
		map[i++] = map_lst->content;
		map_lst = map_lst->next;
	}
	err = (parcer(map, ident, size)) ? 1 : err;
	return (err);
}

int				map(int argc, char **argv, t_ident *ident)
{
	int		fd;
	t_list	*map_lst;
	char	*line;
	int		err;

	err = valid_input(argc, argv);
	if (err)
		invalid_map(err);
	if (!err)
	{
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &line))
			ft_lstadd_back(&map_lst, ft_lstnew(line));
		ft_lstadd_back(&map_lst, ft_lstnew(line));
		err = ((map_parcer(map_lst, ft_lstsize(map_lst), ident))) ? 1 : err;
	}
	return (err);
}
