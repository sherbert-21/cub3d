#include "cub3d.h"

static t_win	*init_game_window_pone(
	void
)
{
	t_win *win;

	if (!(win = malloc(sizeof(t_win))))
	ft_bzero(win, sizeof(t_win));
	if (!(win->mlx = mlx_init()))
	win->x = 400;
	win->y = 400;
	return (win);
}

static int		init_game_window_ptwo(int argc, char **argv, t_win *win)
{
	char	*map_string;

	win->save = 0;
	if (!(file(argc, argv, win)))
		return(ERR);
	if (!(win->win = mlx_new_window(win->mlx,
		win->x, win->y, "Cub3D")))
		return (ERR);
	if(!(win->screen = new_image(win, win->x,
		win->y)))
		return (ERR);
	return (SUCK);
}

int				main(
	int argc,
	char **argv
)
{
	t_win	*win;
	int			fd;

	if (!(win = init_game_window_pone())
		|| init(win, 5)
		|| init_game_window_ptwo(argc, argv, win))
		return (ERR);
	// need_save(win, argv);
	mlx_hook(win->win, 2, 1L << 0, key_pressed, win);
	mlx_hook(win->win, 3, 1L << 1, key_released, win);
	mlx_hook(win->win, 17, 1L << 17, destroy_window, win);
	mlx_loop_hook(win->mlx, loop, win);
	if (win->save != 1)
		mlx_loop(win->mlx);
	return (SUCK);
}

// static void    print_map(t_ident ident, void *mlx, void *win)
// {
//     int i;
//     int j;
//     int x_m;
//     int y_m;
//     int x = (ident.x - ident.len * 15) / 2;
//     int y = (ident.y - ident.size * 15) / 2;

//     i = -1;
//     while (++i < ident.size)
//     {
//         x = ident.x / 2 - ident.len / 2;
//         j = -1;
//         while (++j < ident.len) 
//         {
//             if (ident.map[i][j] == 1)
//             {
//                 for(x_m = 0; x_m < 15; x_m++)
//                 {
//                     for(y_m = 0; y_m < 15; y_m++)
//                         mlx_pixel_put(mlx, win, x + x_m, y + y_m, 0xFF00EF);
//                 }
//             }
//             x += 15;
//         }
//         y += 15;
//     }
//     for (int l = 0; l < 8; l++){
//         for (int m = 0; m < 8; m++){
//             mlx_pixel_put(mlx, win, ident.x / 2 - 4 + m, ident.y / 2 - 4 + l, 0xFFFFFF);
//         }}
// }

// int main(int argc, char **argv)
// {
//     void    *win_1;
//     int     y = -1;
//     int     x = -1;
//     t_win   sxreen;

//     if (!(file(argc, argv, &sxreen)))
//     {
//         sxreen.mlx = mlx_init();
//         sxreen.win = mlx_new_window(sxreen.mlx, parce.x, parce.y, "cub3d");
//         win_1 = mlx_new_window(sxreen.mlx, parce.x, parce.y, "cub2d");
//         print_map(parce, sxreen.mlx, win_1);
//         sxreen.sxreen_ptr = mlx_new_image(sxreen.mlx, parce.x, parce.y);
//         mlx_hook(sxreen.win, 2, 0, &move_events, &parce);
// 	    mlx_hook(sxreen.win, 6, 0, &mouse_move, &parce);
// 	    mlx_hook(sxreen.win, 17, 0, &exit_event, (void*)0);
//         mlx_loop(sxreen.mlx);
//     }
//     return (0);
// }

// int main(int argc, char **argv)
// {
//         sxreen.mlx = mlx_init();
//         sxreen.win = mlx_new_window(sxreen.mlx, parce.x, parce.y, "cub3d");
//         sxreen.sxreen_ptr = mlx_new_image(sxreen.mlx, parce.x, parce.y);
// 	    sxreen.sxreen_data = mlx_get_data_addr(sxreen.mlx, , ,);
//         mlx_hook(sxreen.win, 2, 0, &keyboard_event, &sxreen);
// 	    mlx_hook(sxreen.win, 4, 0, &mouse_event, &sxreen);
// 	    mlx_hook(sxreen.win, 5, 0, &mouse_release, &sxreen);
// 	    mlx_hook(sxreen.win, 3, 0, &key_release, &sxreen);
// 	    mlx_hook(sxreen.win, 6, 0, &mouse_move, &sxreen);
// 	    mlx_hook(sxreen.win, 17, 0, &exit_event, (void*)0);
//         mlx_loop(sxreen.mlx);
//     }
//     return (0);
// }