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
	ft_putendl_fd("Checking file...", 1);
	if (!(file(argc, argv, win)))
		return (ERR);
	ft_putendl_fd("Creating new window...", 1);
	if (!(win->win = mlx_new_window(win->mlx,
		win->x, win->y, "Cub3D")))
		return (invalid_file(0));
	ft_putendl_fd("Starting Cub3D...", 1);
	if(!(win->screen = new_image(win, win->x,
		win->y)))
		return (invalid_file(0));
	ft_putendl_fd("DONE!", 1);
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_win		*win;
	int			succ;

	win = init_win();
	succ = init_game(argc, argv, win);
	succ = (!(init_keybuff(win))) ? 0 : succ;
	if (!succ)
		return (ERR);
	mlx_hook(win->win, 2, 0, key_pressed, win);
	mlx_hook(win->win, 3, 0, key_released, win);
	mlx_loop_hook(win->mlx, loop, win);
	if (win->save != 1)
		mlx_loop(win->mlx);
	return (SUCCESS);
}