#include "cub3d.h"

static int		check_str(char *str, int c, int first_c, t_win *win)
{
	int i;

	if (!str || str[first_c] != c || !(str[first_c + 1] == ' '))
		return (ERR);
	i = first_c + 1;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (ERR);
	return (SUCCESS);
}

static int		get_rgb_from_clr(int r, int g, int b)
{
	int clr;

	clr = r;
	clr = (clr << 8) + g;
	clr = (clr << 8) + b;
	return (clr);
}

static int		get_num_clr(int c, char *str, int *l, t_win *win)
{
	int clr;

	clr = ft_atoi(&str[*l]);
	if (clr < 0 || clr > 255)
		return (-1);
	while (ft_isdigit(str[*l]))
		*l += 1;
	*l += 1;
	return (clr);
}

int				color(char *str, int c, int first_c, t_win *win)
{
	int clr;
	int r;
	int g;
	int b;
	int i;

	clr = 0;
	if (!(check_str(str, c, first_c, win)))
		return (invalid_file(7));
	i = first_c + 1;
	while (str[i] == ' ')
		i++;
	if ((r = get_num_clr(r, str, &i, win)) == -1
		|| (g = get_num_clr(g, str, &i, win)) == -1
		|| (b = get_num_clr(b, str, &i, win)) == -1)
		return (invalid_file(7));
	clr = get_rgb_from_clr(r, g, b);
	if (c == 'F')
		win->clr_f = clr;
	else if (c == 'C')
		win->clr_c = clr;
	return (SUCCESS);
}