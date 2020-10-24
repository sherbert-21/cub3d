#include "cub3d.h"

// err_1 - invalid_input
// err_2 - no_map
// err_3 - invalid_ident
// err_4 - invalid_file
// err_5 - couldn't allocate

void		invalid_file(int err)
{
	ft_putendl_fd("Error\n", 1);
	if (err == 1)
		ft_putendl_fd("Invalid input", 1);
	else if (err == 2)
		ft_putendl_fd("No map", 1);
	else if (err == 3)
		ft_putendl_fd("Invalid identifier or information for object", 1);
	else if (err == 4)
		ft_putendl_fd("Invalid map", 1);
	else if (err == 5)
		ft_putendl_fd("Could't allocate mmry", 1);
}
