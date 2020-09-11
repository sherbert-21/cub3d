#include "cub3d.h"

static void		parse_texture(char *ident, char *texture, t_ident *parse)
{
	if (ident[0] == 'N')
		parse->no_text = texture;
	else if (ident[0] == 'E')
		parse->ea_text = texture;
	else if (ident[0] == 'W')
		parse->we_text = texture;
	else if (ident[0] == 'S' && ident[1] == 'A')
		parse->so_text = texture;
	else
		parse->s_text = texture;
}

static void		parce_color(char ident, int clr, int nill, t_ident *parse)
{
	int		r;
	int		g;
	int		b;

	b = (nill == 4 || nill == 5 || nill == 6 || nill == 7) ? 0 : clr % 1000;
	clr /= 1000;
	g = (nill == 2 || nill == 3 || nill == 6 || nill == 7) ? 0 : clr % 1000;
	clr /= 1000;
	r = (nill == 1 || nill == 3 || nill == 5 || nill == 7) ? 0 : clr % 1000;
	if (ident == 'C')
	{
		parse->c_color_r = r;
		parse->c_color_g = g;
		parse->c_color_b = b;
	}
	else
	{
		parse->f_color_r = r;
		parse->f_color_g = g;
		parse->f_color_b = b;
	}
}

int				resolution(char *ident, t_ident *parse)
{
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	parse->x = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	parse->y = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident)
		return (1);
	return (0);
}

int				color(char *ident, t_ident *parse)
{
	int		clr;
	int		nill;

	clr = 0;
	nill = 0;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		ident++;
	clr = ft_atoi(ident);
	nill = (ft_atoi(ident) == 0) ? 1 : 0;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		ident++;
	clr = clr * 1000 + ft_atoi(ident);
	nill = (ft_atoi(ident) == 0) ? nill + 2 : nill;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		ident++;
	clr = clr * 1000 + ft_atoi(ident);
	nill = (ft_atoi(ident) == 0) ? nill + 4 : nill;
	while (!(*ident >= '0' && *ident <= '9') && *ident)
		ident++;
	if (*ident || clr > 255255255 || clr < 0)
		return (1);
	else
		parce_color(ident[0], clr, nill, parse);
	return (0);
}

int				texture(char *ident, t_ident *parse)
{
	char	*text;
	int		i;
	int		err;
	int		j;

	i = 0;
	j = 2;
	while (ident[j] == ' ' && ident[j])
		j++;
	while (ident[j + i] != ' ' && ident[j + i])
		i++;
	err = (!ident[j]) ? 1 : 0;
	text = (!err) ? ft_calloc(i + 1, sizeof(char)) : NULL;
	err = (!text) ? 1 : err;
	i = 0;
	while (ident[j] != ' ' && ident[j] && !err)
		text[i++] = ident[j++];
	while (ident[j] && ident[j] == ' ' && !err)
		j++;
	err = (ident[j]) ? 1 : err;
	if (!err)
		parse_texture(ident, text, parse);
	save_free(&text);
	return (err);
}
