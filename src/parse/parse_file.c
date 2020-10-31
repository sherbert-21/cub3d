#include "cub3d.h"

int             parse_file(char *path_file, t_raw_game *raw_game)
{
    t_list	*lst;
    int     fd;
    char	*first_map_line;

    if ((fd = open(path_file, O_RDONLY)) < 0)
        return (ERR);
    if (!parse_info_fields(fd, raw_game, &first_map_line))
        return (ERR);
    lst = NULL;

}
