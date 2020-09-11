#include "cub3d.h"

int				valid_input(int argc, char **argv)
{
	if (argc > 3 || argc == 1)
		return (1);
	else
	{
		if (argc == 2)
		{
			if (ft_strnstr(argv[1], "--save", 10))
				return (2);
			else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
				return (1);
		}
		if (argc == 3)
		{
			if (ft_strnstr(argv[1], "--save", 10))
				return (1);
			else if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
				return (1);
		}
	}
	return (0);
}
