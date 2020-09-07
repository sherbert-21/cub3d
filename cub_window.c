#include "./mlx/mlx.h"

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;
    int     x;
    int     y;

    x = 100;
    y = 100;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 600, 600, "cub3d");
    while (y++ < 150)
    {
        x = 100;
        while (x++ < 200)
            mlx_pixel_put(mlx, win, x, y, 0xFF00EF);
    }
    mlx_loop(mlx);
    return (0);
}