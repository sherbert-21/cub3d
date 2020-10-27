#include "cub3d.h"

static int invalid_ident(int err)
{
	if (err == 4)
		ft_putendl_fd("Invalid identifier", 1);
	else if (err == 5)
		ft_putendl_fd("Invalid resolution", 1);
	else if (err == 6)
		ft_putendl_fd("Invalid texture", 1);
	else if (err == 7)
		ft_putendl_fd("Invalid color", 1);
	else if (err == 8)
		ft_putendl_fd("Could't open the file", 1);
	else if (err == 9)
		ft_putendl_fd("Something wrong with number of identifiers", 1);
	return (ERR);
}
int		invalid_file(int err)
{
	ft_putendl_fd("Error", 1);
	if (err == 0)
		ft_putendl_fd("Could't allocate mmry", 1);
	else if (err == 1)
		ft_putendl_fd("Invalid input", 1);
	else if (err == 2)
		ft_putendl_fd("No map", 1);
	else if (err == 3)
		ft_putendl_fd("Invalid map", 1);
	else if (err > 3)
		return(invalid_ident(err));
	return (ERR);
}
