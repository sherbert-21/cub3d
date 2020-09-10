#include "cub3d.h"

int		identifier(char *ident, t_ident *parse)
{
	if (ident[0] == 'R')
		return (resolution(++ident, parse));
	else if (ident[0] == 'F' || ident[0] == 'C')
		return (color(ident, parse));
	else
		return (texture(ident, parse));
}

int				valid_identifier(char *ident, t_ident *parse)
{
	if (ft_strchr("RSF", ident[0]) && ident[1] == ' ')
		return (0);
	else if (ft_strchr("SN", ident[0]) && ident[1] == 'O')
		return (0);
	else if (ident[0] == 'W' && ident[1] == 'E')
		return (0);
	else if (ident[0] == 'E' && ident[1] == 'A')
		return (0);
	else
		return (1);
}
