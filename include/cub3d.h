#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_ident
{
	int			x;
	int			y;
    char        *no_text;
    char        *so_text;
    char        *we_text;
    char        *ea_text;
    char        *s_text;
    int         f_color_r;
    int         f_color_g;
    int         f_color_b;
    int         c_color_r;
    int         c_color_g;
    int         c_color_b;
    int         **map;
}				t_ident;

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

#endif