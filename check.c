#include "cub3d.h"

int		valid_identifier(char *ident, t_ident *parse)
{
	if (ft_strchr("RSF", ident[0]) && ident[1] == ' ')
		return (identifier(ident, parse));
	else if (ft_strchr("SN", ident [0]) && ident[1] == 'O')
		return (identifier(ident, parse));
	else if (ident[0] == 'W' && ident[1] == 'E')
		return (identifier(ident, parse));
	else if (ident[0] == 'E' && ident[1] == 'A')
		return (identifier(ident, parse));
	else
		return (1);
}
