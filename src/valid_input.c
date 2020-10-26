#include "cub3d.h"

int				valid_input(int argc, char **argv, t_win *win)
{
	int i;

	i = ft_strlen(argv[1]) - 1;
	if (argc < 3 && argc > 0)
	{
		if (argc == 2)
		{
			if (!(ft_strncmp(argv[1], "--save", 10)))
				return (invalid_file(2, win));
			else if (argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
				return (invalid_file(1, win));
		}
		if (!(ft_strncmp(argv[1], "--save", 10)) ||
					(argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.') ||
					ft_strncmp(argv[1], "--save", 10))
			return (invalid_file(1, win));
		if (!(ft_strncmp(argv[2], "--save", 10)))
			win->save = 1;
		return (SUCCESS);
	}
	return (invalid_file(1, win));
}
