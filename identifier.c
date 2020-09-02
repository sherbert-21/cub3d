#include "cub3d.h"

// static int     texture(char *ident, t_ident *parse)
// {
// }

static void		parce_color(char ident, int clr, int nill, t_ident *parse)
{
	int r;
	int g;
	int b;

	b = (nill == 4 || nill == 5 || nill == 6 || nill == 7) ? 0 : clr % 1000;
	clr /= 1000;
	g = (nill == 2 || nill == 3 || nill == 6 || nill == 7) ? 0 : clr % 1000;
	clr /= 1000;
	r = (nill == 1 || nill == 3 || nill == 5 || nill == 7) ? 0 : clr % 1000;
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
	int clr;
	int nill;

	clr = 0;
	nill = 0;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	clr = ft_atoi(*ident);
	nill = (ft_atoi(*ident) == 0) ? 1 : 0;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	clr = clr * 1000 + ft_atoi(*ident);
	nill = (ft_atoi(*ident) == 0) ? nill + 2 : nill;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	clr = clr * 1000 + ft_atoi(*ident);
	nill = (ft_atoi(*ident) == 0) ? nill + 4 : nill;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		*ident++;
	if (*ident || clr > 255255255 || clr < 0)
		return (1);
	else
		parce_color(ident[0], clr, nill parse);
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
