/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:55:39 by sherbert          #+#    #+#             */
/*   Updated: 2020/10/29 19:55:40 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

#include <stdio.h>

# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13
# define _LEFT 123
# define _RIGHT 124
//# define _DOWN 125
//# define _UP 126

# define ERR 0
# define SUCCESS 1
# define SKIP 2

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

typedef struct	s_texture
{
	int			width;
	int			height;
	int			size;

	int			bpp;
	int			endian;

	void		*img;
	char		*data;
}				t_texture;

typedef struct			s_sprite
{
    int					x;
    int					y;
}						t_sprite;

typedef struct			s_sprites
{
    int					x;
    int					y;
    struct s_sprites	*next;
}						t_sprites;

typedef struct			s_draw_sprite
{
    t_sprite			*sprites;
    int					i;
    double				spriteX;
    double				spriteY;
    int					width;
    int					height;

    double				invDet;
    double				transformX;
    double				transformY;
    int					spriteScreenX;

    int					drawStartX;
    int					drawEndX;
    int					drawStartY;
    int					drawEndY;

    int					stripe;
    int					y;
    int					d;
    int					texX;
    int					texY;
    int					color;
    int					totcolor;
}						t_draw_sprite;

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
	int         turn_left;
	int         turn_right;
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

typedef struct	s_game
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
    t_texture       **text;
    t_texture       *sprite;
    t_sprites   *sprite_screen;
	t_texture		*screen;
    t_ray       *ray;
	t_keybuff	*keybuff;
}               t_game;

typedef struct  s_raw_game
{
    int         win_h;
    int         win_w;
    int         need_save;
    char        *north_texture_path;
    char        *south_texture_path;
    char        *west_texture_path;
    char        *east_texture_path;
    char        *sprite_texture_path;
    int			floor_color;
	int			ceilling_color;
	char		**map;
	int			maw_w;
	int 		map_h;
}               t_raw_game;

int		        ft_strisnum(char *str);
int             ft_numwords(char const *s, char c);
int             parse_file(char *path_file, t_raw_game *raw_game);
int             parse_info_fields(int fd, t_raw_game *raw_game, char **first_map_line);
int				parse_ceilling_floor_color(char **splitted_line, t_raw_game *raw_game);
int				parse_map(int fd, char *first_map_line, t_raw_game *raw_game);
int			    invalid_file(int err);
int				valid_input(int argc, char **argv, t_raw_game *game);
int				ident_parce(char *line, t_game *win);
int				resolution(char *ident, int i, t_game *win);
int				parse_texture(char *path, t_raw_game *raw_game);
int				color(char *str, int c, int first_c, t_game *win);
int				map_parce(char **map, int i, int size, t_game *win);
int 	        set_pos(t_game *win, char dir, int x, int y);

int				init_plr(t_game *win);
int				init_keybuff(t_game *win);
int				init_sprite(t_game *win);
int				init_text(t_game *win, int nbr);

int 	     	move_events(t_game *win);
void            turn_right(t_game *win);
void            turn_left(t_game *win);
int				ray(t_game *win);
void			perp_and_height(t_ray *ray, t_player *plr, t_game *win);
void			hit(t_ray *ray, t_game *win);
int				create_bmp(t_texture *screen, char *name);
void			pixel_put(int clr, int x, int y, t_texture *screen);
void			ver_line_clr_image(t_line *line, t_game *win, int clr);
void			ver_line_text_pic(t_line *line, t_game *win,
                                  t_texture *text, t_ray *ray);
t_texture			*new_image(t_game *win);
void			texturisation(t_ray *ray, t_game *win);
void			is_sprite(t_ray *ray, t_game *win);
void			sort_sprite(t_game *win, t_sprite *sprites, int nbr);
t_sprite		*list_to_tab(t_game *win);
int				draw_sprite(t_ray *ray, t_game *win);

int				key_pressed(int key, void *param);
int				key_released(int key, void *param);
int				loop(void *param);
int		        destroy_window(void *param);

void    		free_str(char ***str);

int				ft_strlen_err(char *str);
char			*ft_strdup_err(char *s, int *ret);
char			*ft_strjoin_err(char *s1, char *s2, int *ret);
char			*ft_strcpy_err(char *dest, char *src);
void			save_free(char **str);
int				get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
#endif
