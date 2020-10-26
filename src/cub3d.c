#include "cub3d.h"

static t_win	*init_win(void)
{
	t_win *win;

	if (!(win = malloc(sizeof(t_win))))
		return (ERR);
	ft_bzero(win, sizeof(t_win));
	if (!(win->mlx = mlx_init()))
		return (ERR);
	win->x = 400;
	win->y = 400;
	return (win);
}

static int		init_game(int argc, char **argv, t_win *win)
{
	char	*map_string;

	if (!(file(argc, argv, win)))
		return(ERR);
	if (!(win->win = mlx_new_window(win->mlx,
		win->x, win->y, "Cub3D")))
		return (ERR);
	if(!(win->screen = new_image(win, win->x,
		win->y)))
		return (ERR);
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_win	*win;
	int			fd;

	if (!(win = init_win())
		|| !init(win, 5)
		|| !init_game(argc, argv, win))
		return (ERR);
	mlx_hook(win->win, 2, 1L << 0, key_pressed, win);
	mlx_hook(win->win, 3, 1L << 1, key_released, win);
	mlx_hook(win->win, 17, 1L << 17, destroy_window, win);
	mlx_loop_hook(win->mlx, loop, win);
	if (win->save != 1)
		mlx_loop(win->mlx);
	return (SUCCESS);
}