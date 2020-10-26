#include "cub3d.h"

int				resolution(char *ident, t_win *win)
{
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (invalid_file(5));
	win->x = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident == '0' || !*ident)
		return (invalid_file(5));
	win->y = ft_atoi(ident);
	while (*ident == ' ' && *ident)
		ident++;
	if (*ident)
		return (invalid_file(5));
	return (0);
}
