#include "cub3d.h"



int             parse_resolution(char *line, t_raw_game *raw_game)
{
    char    **splitted_line;

    splitted_line = ft_split(line, ' ');
    if (splitted_line[0][0] != 'R' || !ft_strisnum(splitted_line[1]) || !ft_strisnum(splitted_line[2]))
        return (ERR);
    raw_game->win_w = ft_atoi(splitted_line[1]);
    raw_game->win_h = ft_atoi(splitted_line[2]);
    return (SUCCESS);
}

int             get_wall_texture_paths(char **splitted_line, t_raw_game *raw_game)
{
    if (ft_strlen(splitted_line[1]) < 3 || splitted_line[1][0] != '.' || splitted_line[1][0] != '/')
        return (invalid_file(6));
    if (splitted_line[0][0] == 'N' && splitted_line[0][1] == 'O')
        raw_game->north_texture_path = ft_strdup(splitted_line[1]);
    else if (splitted_line[0][0] == 'S' && splitted_line[0][1] == 'O')
        raw_game->south_texture_path = ft_strdup(splitted_line[1]);
    else if (splitted_line[0][0] == 'W' && splitted_line[0][1] == 'E')
        raw_game->west_texture_path = ft_strdup(splitted_line[1]);
    else if (splitted_line[0][0] == 'E' && splitted_line[0][1] == 'A')
        raw_game->east_texture_path = ft_strdup(splitted_line[1]);
    return (SUCCESS);
}

int             line_is_part_map_or_incorrect(char *line)
{
    char **splitted_line;
    int i;

    splitted_line = ft_split(line, ' ');
    if (ft_strlen(splitted_line[0]) == 2 && ft_numwords(line, ' ') == 2 &&
    	((splitted_line[0][0] == 'N' && splitted_line[0][1] == 'O') ||
        (splitted_line[0][0] == 'S' && splitted_line[0][1] == 'O') ||
        (splitted_line[0][0] == 'W' && splitted_line[0][1] == 'E') ||
        (splitted_line[0][0] == 'E' && splitted_line[0][1] == 'A')))
        return (0);
	if (ft_strlen(splitted_line[0]) == 1 && ft_numwords(line, ' ') == 3 && splitted_line[0][0] == 'R')
		return (0);
	if (ft_strlen(splitted_line[0]) == 1 && ft_numwords(line, ' ') == 2 &&
        (splitted_line[0][0] == 'S' || splitted_line[0][0] == 'F' || splitted_line[0][0] == 'C'))
        return (0);
    i = -1;
    while (line[++i])
    {
        if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1' || line[i] == '2' ||
            line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
            return (-1);
    }
    return (1);
}

int             is_all_field_read(t_raw_game *raw_game)
{
    if (!raw_game->east_texture_path || !raw_game->west_texture_path ||
        !raw_game->south_texture_path || !raw_game->north_texture_path ||
        !raw_game->sprite_texture_path ||
        raw_game->win_w == 0 || raw_game->win_h == 0)
        return (0);
    return (1);
}

int             parse_info_fields(int fd, t_raw_game *raw_game, char **first_map_line)
{
    int     succ;
    char	*line;
    char    **splitted_line;

    while (get_next_line(fd, &line) && line[0])
	{
		if ((succ = line_is_part_map_or_incorrect(line)) && succ != 0)
		{
			if (succ == 1)
			{
				if (!is_all_field_read(raw_game))
					return (ERR);
			}
			else if (succ == -1)
				return (ERR);
			*first_map_line = line;
			return (SUCCESS);
		}
		else if (ft_numwords(line, ' ') == 3)
		{
			if (!parse_resolution(line, raw_game))
				return (ERR);
		}
		else if (ft_numwords(line, ' ') == 2)
		{
			splitted_line = ft_split(line, ' ');
			if (ft_strlen(splitted_line[0]) == 2)
			{
				if (!get_wall_texture_paths(splitted_line, raw_game))
					return (invalid_file(6));
			}
			else if (ft_strlen(splitted_line[0]) == 1 && splitted_line[0][0] == 'S')
			{
				if (ft_strlen(splitted_line[1]) < 3 || splitted_line[1][0] != '.' || splitted_line[1][0] != '/')
					return (invalid_file(6));
				raw_game->sprite_texture_path = ft_strdup(splitted_line[1]);
			}
			else if (ft_strlen(splitted_line[0]) == 1 && (splitted_line[0][0] == 'F' || splitted_line[0][0] == 'C'))
			{
				if (!parse_ceilling_floor_color(splitted_line, raw_game))
					return (ERR);
			}
			else
				return (ERR);
		}
		else
			return (ERR);
		free(line);
	}
	return (ERR);
}
