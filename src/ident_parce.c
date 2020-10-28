#include "cub3d.h"

static int		valid_identifier(char *ident)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ft_strchr("RSFC", ident[i]) && ident[i + 1] == ' ')
		return (SUCCESS);
	else if (ft_strchr("SN", ident[i]) && ident[i + 1] == 'O')
		return (SUCCESS);
	else if (ident[i] == 'W' && ident[i + 1] == 'E')
		return (SUCCESS);
	else if (ident[i] == 'E' && ident[i + 1] == 'A')
		return (SUCCESS);
	else
		return (invalid_file(4));
}

static int		set_ident(char *ident, t_win *win)
{
	int i;

	i = 0;
	while (ident[i] == ' ')
		i++;
	if (ident[i] == 'R')
		return (resolution(ident, ++i, win));
	else if (ident[i] == 'F' || ident[i] == 'C')
		return (color(ident, ident[i], i, win));
	else
		return (texture(ident, i, win));
}

int			ident_parce(char *line, t_win *win)
{
	while (*line == ' ')
		line++;
	if (*line == '\n' || !*line)
		return (SKIP);
	if (!(valid_identifier(line)))
		return (ERR);
	if (!(set_ident(line, win)))
		return (ERR);
	return (SUCCESS);
}