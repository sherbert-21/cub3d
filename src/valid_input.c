#include "cub3d.h"

// static int		valid_input2(int argc, char **argv)
// {
// 	int i;

// 	ft_putendl_fd("hui1",  1);
// 	i = ft_strlen(argv[1]);
// 	if (!(ft_strncmp(argv[1], "--save", 7)) ||
// 					!(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) ||
// 					ft_strncmp(argv[1], "--save", 7))
// 		return (invalid_file(1));
// 	return (SUCCESS);
// }

// int				valid_input(int argc, char **argv, t_win *win)
// {
// 	int i;

// 	i = ft_strlen(argv[1]);
// 	win->save = 0;
// 	if (argc < 3 && argc > 0)
// 	{
// 		if (argc == 2)
// 		{
// 			if (!(ft_strncmp(argv[1], "--save", 7)))
// 				return (invalid_file(2));
// 			else if (!(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))))
// 				return (invalid_file(1));
// 		}
// 		if (argc == 3)
// 			valid_input2(argc, argv);
// 		if (!(ft_strncmp(argv[2], "--save", 7)) 
// 			|| !(ft_strncmp(argv[1], "--save", 7)))
// 			win->save = 1;
// 		return (SUCCESS);
// 	}
// 	ft_putendl_fd("hui2",  1);
// 	return (invalid_file(1));
// }


//(file[file_len - 1] != 'm' || file[file_len - 2] != 'p'
		// || file[file_len - 3] != 'x' || file[file_len - 4] != '.')
