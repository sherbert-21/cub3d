#include "cub3d.h"

static void    print_map(t_ident ident, void *mlx, void *win)
{
    int i;
    int j;
    int x_m;
    int y_m;
    int x = ident.x / 2 - ident.size * 5;
    int y = ident.y / 2 - ident.len * 5;

    i = -1;
    while (++i < ident.size)
    {
        x = ident.x / 2 - ident.size * 15;
        j = -1;
        while (++j < ident.len)
        {
            if (ident.map[i][j] == 1)
            {
                for(x_m = 0; x_m < 15; x_m++)
                {
                    for(y_m = 0; y_m < 15; y_m++)
                        mlx_pixel_put(mlx, win, x + x_m, y + y_m, 0xFF00EF);
                }
            }
            x += 15;
        }
        y += 15;
    }
}

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;
    int     y = -1;
    int     x = -1;
    t_ident parce;

    if (!(map(argc, argv, &parce)))
    {
        mlx = mlx_init();
        win = mlx_new_window(mlx, parce.x, parce.y, "cub3d");
        print_map(parce, mlx, win);
        mlx_loop(mlx);
    }
    return (0);
}