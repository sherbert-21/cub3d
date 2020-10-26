#include "cub3d.h"

int				valid_input(int argc, char **argv, t_win *win)
{
	int i;

	i = ft_strlen(argv[1]) - 1;
	if (argc < 3 && argc > 0)
	{
		if (argc == 2)
		{
			if (argv[1] == "--save")
				return (invalid_file(2));
			else if (argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
				return (invalid_file(1));
		}
		if (argv[1] == "--save")
			return (invalid_file(1));
		else if (argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
			return (invalid_file(1));
	}
	if (argv[2] == "--save")
		win->save = 1;
	return (SUCK);
}
