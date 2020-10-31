#include "cub3d.h"

int				parse_map(int fd, char *first_map_line, t_raw_game *raw_game)
{
    char    *line;
    int     current_line_size;
    int     was_empty;
    int     i;


    while (get_next_line(fd, &line))
    {
        i = -1;
        current_line_size = ft_strlen(line);
        if (current_line_size > raw_game->map_w)
            raw_game->map_w = current_line_size;
        while(++i < current_line_size)
        {
            was_empty = 0;
            if (line[i] == 0)
            {
                if (i == 0 || i == current_line_size - 1 || raw_game->map_h == 0)
                    return -1;
                was_empty = 1;
            }
            raw_game->map_h++;
        }
        if (was_empty)
            return -1;
    }
}
