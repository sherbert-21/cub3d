#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define A 0
# define S 1
# define D 2
# define W 13
# define _LEFT 123
# define _RIGHT 124
# define _DOWN 125
# define _UP 126

typedef struct  s_player
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    int         mapX;
    int         mapY;
    double      planeX;
    double      planeY;

    double      cameraX;

    double      rayDirX;
    double      rayDirY;

    double      perpWallDist;

    double      delDistX;
    double      delDistY;

    double      speed;
    double      rotation;
}               t_player;

typedef struct	s_pic
{
	int			width;
	int			height;
	int			size;
	int			bpp;
	int			endian;
	void		*img;
	char		*data;
}				t_pic;

// typedef struct	s_sprite
// {
// 	int			i;
// 	double		sprite_x;
// 	double		sprite_y;
// 	double		inv_det;
// 	double		transform_x;
// 	double		transform_y;
// 	int			sprite_screen_x;
// 	int			sprite_height;
// 	int			draw_start_y;
// 	int			draw_end_y;
// 	int			sprite_width;
// 	int			draw_start_x;
// 	int			draw_end_x;
// 	int			stripe;
// 	int			y;
// 	int			d;
// 	int			tex_x;
// 	int			tex_y;
// 	int			color;
// 	int			totcolor;
// }				t_sprite;

typedef struct	s_win
{
    void        *mlx;
    void        *win;
    void        *img_data;

	int			x;
	int			y;
    int         clr_c;
    int         clr_f;
    int         **map;
    int         save;
    size_t      len;
    size_t      size;
    t_player    *plr;
    t_pic       **text;
    t_pic       *sprite;
    // t_sprite    *sprite_screen;
}               t_win;

int				file(int argc, char **argv, t_ident *ident);
void		    invalid_file(int err);
int				valid_input(int argc, char **argv);
int				resolution(char *ident, t_ident *parse);
int				texture(char *ident, t_ident *parse);
int				color(char *str, int c, int first_c, t_ident *i);
int				map(char **map, int i, int size, t_ident *ident);
int 	        set_pos(t_win *win, char dir, int cursor, int u)

int 	        move_events(int key, t_win *win);

#endif