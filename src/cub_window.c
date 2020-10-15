#include "cub3d.h"

static void    print_map(t_ident ident, void *mlx, void *win)
{
    int i;
    int j;
    int x_m;
    int y_m;
    int x = (ident.x - ident.len * 15) / 2;
    int y = (ident.y - ident.size * 15) / 2;

    i = -1;
    while (++i < ident.size)
    {
        x = ident.x / 2 - ident.len / 2;
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
    for (int l = 0; l < 8; l++){
        for (int m = 0; m < 8; m++){
            mlx_pixel_put(mlx, win, ident.x / 2 - 4 + m, ident.y / 2 - 4 + l, 0xFFFFFF);
        }}
}

int main(int argc, char **argv)
{
    t_img   img;
    void    *win_1;
    int     y = -1;
    int     x = -1;
    t_ident parce;

    if (!(map(argc, argv, &parce)))
    {
        img.mlx = mlx_init();
        img.win = mlx_new_window(img.mlx, parce.x, parce.y, "cub3d");
        win_1 = mlx_new_window(img.mlx, parce.x, parce.y, "cub2d");
        print_map(parce, img.mlx, win_1);
        img.img_ptr = mlx_new_image(img.mlx, parce.x, parce.y);
        mlx_hook(img.win, 2, 0, &move_events, &parce);
	    mlx_hook(img.win, 6, 0, &mouse_move, &img);
	    mlx_hook(img.win, 17, 0, &exit_event, (void*)0);
        mlx_loop(img.mlx);
    }
    return (0);
}

// int main(int argc, char **argv)
// {
//         img.mlx = mlx_init();
//         img.win = mlx_new_window(img.mlx, parce.x, parce.y, "cub3d");
//         img.img_ptr = mlx_new_image(img.mlx, parce.x, parce.y);
// 	    img.img_data = mlx_get_data_addr(img.mlx, , ,);
//         mlx_hook(img.win, 2, 0, &keyboard_event, &img);
// 	    mlx_hook(img.win, 4, 0, &mouse_event, &img);
// 	    mlx_hook(img.win, 5, 0, &mouse_release, &img);
// 	    mlx_hook(img.win, 3, 0, &key_release, &img);
// 	    mlx_hook(img.win, 6, 0, &mouse_move, &img);
// 	    mlx_hook(img.win, 17, 0, &exit_event, (void*)0);
//         mlx_loop(img.mlx);
//     }
//     return (0);
// }