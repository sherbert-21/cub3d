#include "cub3d.h"

int				resolution(char *ident, t_win *win)
{
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	win->x = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (1);
	win->y = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident)
		return (1);
	return (0);
}
