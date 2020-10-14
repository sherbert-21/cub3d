#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <cmath.h>

struct          s_player
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
};

struct  s_color
{
    int         f_r;
    int         f_g;
    int         f_b;
    int         c_r;
    int         c_g;
    int         c_b;
};

struct  s_text
{
    char        *no;
    char        *so;
    char        *we;
    char        *ea;
    char        *s;
};

typedef struct	s_ident
{
	int			x;
	int			y;
    int         **map;
    size_t      len;
    size_t      size;
    struct      s_player player;
    struct      s_color color;
    struct      s_text text;
}               t_ident;

typedef struct s_img
{
    void        *mlx;
    void        *win;
    void        *img_ptr;
    void        *img_data;
}               t_img;

// parse
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

#endif