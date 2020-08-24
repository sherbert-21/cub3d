#include "cub3d.h"

// err_1 - invalid_input
// err_2 - no_map
// err_3 - invalid_ident
// err_4 - invalid_map

// сделать отправку структуры со всеми данными по мапе
static  void     invalid_map(int err)
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
}

void    parcer(char **map, t_ident *ident, int size)
{
    int i = 0;
    int err;
    int j;

    while (map[i] && map[i][0] != ' ')
    {
        if (!(err = valid_identifier(map[i])))
            identifier(map[i], ident);
        else if (!map[i][0])
            continue;
        i++;
        if (err)
            invalid_map(3);
    }
    err = check_map(map, i, size);
    if (err)
        invalid_map(4);
    while (map[i])
        print_map(map[i++]);
}

void    map_parcer(t_list **map_lst, int size, t_ident *ident)
{
    char    **map;
    int     i = -1;
    t_list  *tmp = *map_lst;

    map = ft_calloc(size + 1, sizeof(char *));
    if (map)
    {
        while (tmp)
        {
            map[i] = ft_calloc(ft_strsize(tmp->content), sizeof(char));
            map[++i] = tmp->content;
            tmp = tmp->next;
        }
        parcer(map, ident, size);
    }
}

int     map(int argc, char **argv)
{
    t_ident ident;
    int     fd;
    t_list  *map_lst;
    char    *line;
    int     err;

    err = valid_input(argc, argv);
    if (!err)
    {
        fd = open(argv[1], O_RDONLY);
        while (get_next_line(fd, &line))
            ft_lstadd_back(&map_lst, ft_lstnew(line));
        ft_lstadd_back(&map_lst, ft_lstnew(line));
        map_parcer(&map_lst, ft_lstsize(map_lst), &ident);
    }
    else
        invalid_map(err);
}
