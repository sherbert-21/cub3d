#include "cub3d.h"

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;
    int     y;
    int     x;
    t_ident parce;

    if (!map(argc, argv, &parce))
    {
        mlx = mlx_init();
        win = mlx_new_window(mlx, parce.x, parce.y, "cub3d");
        while (y++ < 150)
        {
            x = 100;
            while (x++ < 200)
                mlx_pixel_put(mlx, win, x, y, 0xFF00EF);
        }
        mlx_loop(mlx);
    }
    return (0);
}