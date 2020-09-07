#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
#include "./mlx/mlx.h"

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
int             valid_identifier(char *ident);
int             valid_input(int argc, char **argv);
int             check_map(char **map, int i, int size);
void		    save_free_map(char ***str);
int		        color(char *ident, t_ident *parse);
int		        resolution(char *ident, t_ident *parse);
void		    parce_color(char ident, int clr, int nill, t_ident *parse);
int             texture(char *ident, t_ident *parse);
