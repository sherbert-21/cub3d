#include "/libft/libft.h"
#include "/gnl/get_next_line.h"

typedef struct	s_ident
{
	int			x;
	int			y;
    char        *no_text;
    char        *so_text;
    char        *we_text;
    char        *ea_text;
    char        *s_text;
    char        *f_color[11];
    char        *c_color[11];
}				t_ident;

int     valid_identifier(char *ident);