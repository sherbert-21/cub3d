#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13
# define _LEFT 123
# define _RIGHT 124
# define _DOWN 125
# define _UP 126

# define ERR 0
# define SUCK 1

typedef struct  s_player
{
    double      posX;
    double      posY;

    double      dirX;
    double      dirY;

    double      planeX;
    double      planeY;

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

typedef struct	s_ray
{
	int			pix;

	int			mapX;
	int			mapY;

	double		cameraX;

	double		rayDirX;
	double		rayDirY;

	double		sideDistX;
	double		sideDistY;

	double		deltaDistX;
	double		deltaDistY;

	double		perpWallDist;

	int			stepX;
	int			stepY;

	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	double		*z_buffer;
}				t_ray;

typedef struct	s_keybuff
{
	int			forward;
	int			backward;
	int			left;
	int			right;
}				t_keybuff;

typedef struct	s_line
{
	int			x;
	int			y;
	int			y0;
	int			y1;

	int			texX;
	int			texY;
}				t_line;

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
	t_pic		*screen;
    t_ray       *ray;
	t_keybuff	*keybuff;
}               t_win;

int				file(int argc, char **argv, t_win *win);
int			    invalid_file(int err);
int				valid_input(int argc, char **argv, t_win *i);
int				resolution(char *ident, t_win *parse);
int				texture(char *str, t_win *win);
int				color(char *str, int c, int first_c, t_win *i);
int				map_parce(char **map, int i, int size, t_win *win);
int 	        set_pos(t_win *win, char dir, int x, int y);
int				init(t_win *win, int i);

int 	     	move_events(int key, t_win *win);
int				ray(t_win *win);
void			perp_and_height(t_ray *ray, t_player *plr, t_win *win);
void			hit(t_ray *ray, t_win *win);
int				create_bmp(t_pic *screen, char *name);
void			pixel_put(int clr, int x, int y, t_pic *screen);
void			ver_line_clr_image(t_line *line, t_win *win, int clr);
void			ver_line_text_pic(t_line *line, t_win *win, 
								t_pic *text, t_ray *ray);
t_pic			*new_image(t_win *win, int x_len, int y_len);
void			texturisation(t_ray *ray, t_win *win);

int				key_pressed(int key, void *param);
int				key_released(int key, void *param);
int				loop(void *param);
int				destroy_window(void *param);

void    		free_str(char ***str);

int				ft_strlen_err(char *str);
char			*ft_strdup_err(char *s, int *ret);
char			*ft_strjoin_err(char *s1, char *s2, int *ret);
char			*ft_strcpy_err(char *dest, char *src);
void			save_free(char **str);
int				get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
#endif