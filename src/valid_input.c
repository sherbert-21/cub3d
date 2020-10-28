#include "cub3d.h"

static int		valid_input2(char **argv)
{
	int i;

	ft_putendl_fd("hui1",  1);
	i = ft_strlen(argv[1]) - 1;
	if (!(ft_strncmp(argv[1], "--save", 7)) ||
		(argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
		argv[1][i - 2] != 'c' || argv[1][i - 3] != '.') ||
		ft_strncmp(argv[1], "--save", 7))
		return (invalid_file(1));
	return (SUCCESS);
}

int				valid_input(int argc, char **argv, t_win *win)
{
	int i;

	i = ft_strlen(argv[1]) - 1;
	win->save = 0;
	if (argc < 3 && argc > 0)
	{
		if (argc == 2)
		{
			if (!(ft_strncmp(argv[1], "--save", 7)))
				return (invalid_file(2));
			else if (argv[1][i] != 'b' || argv[1][i - 1] != 'u' ||
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.')
				return (invalid_file(1));
		}
		if (argc == 3)
		{
			i = valid_input2(argv);
			if (!(ft_strncmp(argv[2], "--save", 7)))
			win->save = 1;
		}
		return ((i) ? SUCCESS : ERR);
	}
	return (invalid_file(1));
}
