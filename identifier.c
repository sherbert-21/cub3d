#include "cub3d.h"

// static int     texture(char *ident, t_ident *parse)
// {
// }
// проверить можно ли запихнуть все цвета в 1 инт с помощью умножения на 1к

static void		parce_color(char ident, int r, int g, int b, t_ident *parse)
{
	if (ident == 'C')
	{
		parse.c_color_r = r;
		parse.c_color_g = g;
		parse.c_color_b = b;
	}
	else
	{
		parse.f_color_r = r;
		parse.f_color_g = g;
		parse.f_color_b = b;
	}
}

static int		resolution(char *ident, t_ident *parse)
{
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	parse.x = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	parse.y = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident)
		return (1);
	return (0);
}

static int		color(char *ident, t_ident *parse)
{
	int r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	r = ft_atoi(*ident);
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	g = ft_atoi(*ident);
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	b = ft_atoi(*ident);
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	if (*ident || r > 255 || g > 255 ||  b > 255 || r < 0 || g < 0 || g < 0)
		return (1);
	else
		parce_color(ident[0], r, g, b, parse);
	return (0);
}

static int		identifier(char *ident, t_ident *parse)
{
	if (ident[0] == 'R')
		return (resolution(++ident, parse));
	else if (ident[0] == 'F' || ident[0] == 'C')
		return (color(ident, parse));
	else
		return (texture(ident, parse));
}

int		valid_identifier(char *ident, t_ident *parse)
{
	if (ft_strchr("RSF", ident[0]) && ident[1] == ' ')
		return (identifier(ident, parse));
	else if (ft_strchr("SN", ident[0]) && ident[1] == 'O')
		return (identifier(ident, parse));
	else if (ident[0] == 'W' && ident[1] == 'E')
		return (identifier(ident, parse));
	else if (ident[0] == 'E' && ident[1] == 'A')
		return (identifier(ident, parse));
	else
		return (1);
}
