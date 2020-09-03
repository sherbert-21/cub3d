#include "cub3d.h"

// err_1 - invalid_input
// err_2 - no_map
// err_3 - invalid_ident
// err_4 - invalid_map
// err_5 - couldn't allocate

// сделать отправку структуры со всеми данными по мапе

void			save_free_map(char ***str)
{
	while (*str)
	{
		if (*str && **str)
		{
			free(**str);
			**str = NULL;
		}
		*str++;
	}
	free(*str);
	*str = NULL;
}

static void		invalid_map(int err)
{
	ft_putendl("Error", 1);
	if (err == 1)
		ft_putstr("Invalid input", 1);
	else if (err == 2)
		ft_putstr("No map", 1);
	else if (err == 3)
		ft_putstr("Invalid identifier or information for object", 1);
	else if (err == 4)
		ft_putstr("Invalid map", 1);
	else if (err == 5)
		ft_putstr("Could't allocate mmry", 1);
}

static int		parcer(char **map, t_ident *ident, int size)
{
	int i;
	int err;
	int j;

	i = 0;
	while (map[i] && map[i][0] != ' ' && !err)
	{
		if (map[i][0] == '\n')
		{
			i++;
			continue;
		}
		if (!(err = valid_identifier(map[i])))
			identifier(map[i], ident);
		i++;
		if (err)
			invalid_map(3);
	}
	err = ((check_map(map, i, size))) ? 1 : err;
	if ((check_map(map, i, size)))
		invalid_map(4);
	return (err);
}

static int		map_parcer(t_list **map_lst, int size, t_ident *ident)
{
	char	**map;
	int		i;
	t_list	*tmp;
	int		err;

	i = -1;
	*tmp = *map_lst;
	map = ft_calloc(size + 1, sizeof(char *));
	err = (!map) ? 1 : 0;
	if (map && !err)
	{
		while (tmp && !err)
		{
			if (!(map[i] = ft_calloc(ft_strsize(tmp->content), sizeof(char))))
				err = 1;
			map[++i] = tmp->content;
			tmp = tmp->next;
		}
		err = ((parcer(map, ident, size))) ? 1 : err;
	}
	save_free_map(&map);
	return (err);
}

int				map(int argc, char **argv)
{
	t_ident ident;
	int		fd;
	t_list	*map_lst;
	char	*line;
	int		err;

	err = valid_input(argc, argv);
	if (err)
		invalid_map(err);
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&map_lst, ft_lstnew(line));
	ft_lstadd_back(&map_lst, ft_lstnew(line));
	err = ((map_parcer(&map_lst, ft_lstsize(map_lst), &ident))) ? 1 : err;
	ft_lstfree(&map_lst);
	return (err);
}
