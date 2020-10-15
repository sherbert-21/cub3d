#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef struct  s_player
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
}               t_player;

typedef struct  s_color
{
    int         f_r;
    int         f_g;
    int         f_b;
    int         c_r;
    int         c_g;
    int         c_b;
}               t_color;

typedef struct  s_text
{
    char        *no;
    char        *so;
    char        *we;
    char        *ea;
    char        *s;
}               s_text;

typedef struct	s_ident
{
	int			x;
	int			y;
    int         **map;
    size_t      len;
    size_t      size;
    t_player    *player;
    t_color     *color;
    t_text      *text;
}               t_ident;

typedef struct  s_img
{
    void        *mlx;
    void        *win;
    void        *img_ptr;
    void        *img_data;

    int			endian;
	int			size_line;
    int         bpp;

    int			mouse_x;
	int			mouse_y;
    float		angle_x;
	float		angle_z;
    int			spin_z;
	int			spin_x;
}               t_img;

int				map(int argc, char **argv, t_ident *ident);
void			save_free_map(char ***str);
int				check_map(char **map, int i, int size, t_ident *ident);
int				valid_input(int argc, char **argv);
int				valid_identifier(char *ident);
int		        identifier(char *ident, t_ident *parse);
int				resolution(char *ident, t_ident *parse);
int				color(char *ident, t_ident *parse);
int				texture(char *ident, t_ident *parse);
int				player_check(char **map, int i, int k, t_ident *ident);

int		        mouse_move(int x, int y, t_img *img);
int 	        move_events(int keycode, t_img *img);
int		        exit_event(void *param);

#endif