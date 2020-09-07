#include "cub3d.h"

int main(int argc, char **argv)
{
    void    *mlx = NULL;
    void    *win = NULL;
    t_ident map;
    int     err;

    err = map(argc, argv, &map);
    mlx = mlx_init();
    win = mlx_new_window(mlx, t_ident.x, t_ident.y, "cub3d");
    mlx_loop(mlx);
    return (0);
}