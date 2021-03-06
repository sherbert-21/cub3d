/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sherbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:58:48 by sherbert          #+#    #+#             */
/*   Updated: 2020/11/09 19:24:55 by sherbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define ESC 53
# define A 0
# define S 1
# define D 2
# define W 13
# define _LEFT 123
# define _RIGHT 124
# define ERROR 0
# define SUCCESS 1

# define ERR 0
# define SUCCESS 1
# define NEXT 2

typedef struct			s_player
{
	double				pos_x;
	double				pos_y;

	double				dir_x;
	double				dir_y;

	double				plane_x;
	double				plane_y;

	double				speed;
	double				rotation;
}						t_player;

typedef struct			s_pic
{
	int					width;
	int					height;
	int					size;

	int					bpp;
	int					endian;

	void				*img;
	int					*data;
}						t_pic;

typedef struct			s_ray
{
	int					pix;

	int					map_x;
	int					map_y;

	double				camera_x;

	double				dir_x;
	double				dir_y;

	double				side_dist_x;
	double				side_dist_y;

	double				delta_dist_x;
	double				delta_dist_y;

	double				perp_wall_dist;

	int					step_x;
	int					step_y;

	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;

	double				*z_buff;
}						t_ray;

typedef struct			s_keybuffer
{
	int					forward;
	int					backward;
	int					left;
	int					right;
	int					turn_left;
	int					turn_right;
}						t_keybuffer;

typedef struct			s_line
{
	int					x;
	int					y;
	int					y0;
	int					y1;
	int					tex_x;
	int					tex_y;
}						t_line;

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
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
	int					stripe;
	int					y;
	int					d;
	int					tex_x;
	int					tex_y;
	int					totcolor;
}						t_draw_sprite;

typedef struct			s_cub
{
	int					width;
	int					height;
	void				*mlx;
	void				*win;
	void				*img;

	char				*path_no;
	char				*path_we;
	char				*path_so;
	char				*path_ea;
	char				*path_s;
	int					clr_ceilling;
	int					clr_floor;
	int					map_x;
	int					map_y;
	int					**map;

	int					save_bmp;

	t_player			*plr;
	t_ray				*ray;
	t_pic				**texture;
	t_pic				*screen;
	t_sprites			*sprites_on_screen;
	t_keybuffer			*keybuffer;
}						t_cub;

void					err_exit(int err_code);
void					init_texture(t_cub *cub, int nbr);
void					init_plr(t_cub *cub);
void					init_game_keybuffer(t_cub *cub);
int						init_game_sprite(t_cub *cub);
t_pic					*new_pic(t_cub *cub, int x_len, int y_len);

void					file_parce(int argc, char **argv, t_cub *cub);
void					valid_input(int argc, char **argv, t_cub *cub);

void					parce_ident(t_list **file_lst, t_cub *cub);
void					resolution(char *ident, t_cub *cub);
void					color(char *ident, t_cub *cub);
void					texture(char *ident, t_cub *cub);

void					parce_map(t_list **file, t_cub *cub);
void					check_symbol(char **tmp, int j, int k);
void					check_square(char **tmp, t_cub *cub);
char					**file_into_map(t_list *file, t_cub *cub);
void					set_dir(char dir, int x, int y, t_cub *cub);

int						loop(void *param);
int						move_events(t_cub *cub);
void					turn_left(t_cub *cub);
void					turn_right(t_cub *cub);
int						key_pressed(int key, void *param);
int						key_released(int key, void *param);

int						ray(t_cub *cub);
void					hit(t_ray *ray, t_cub *cub);
void					perp_and_height(t_ray *ray, t_player *plr, t_cub *cub);
void					texturisation(t_ray *ray, t_cub *cub);
t_sprite				*list_to_tab(t_cub *cub);
void					is_sprite(t_ray *ray, t_cub *cub);
void					draw_sprite(t_ray *ray, t_cub *cub);

void					ver_line_color_pic(t_line *line, t_cub *cub, int color);
void					ver_line_texture_pic(t_line *line, t_cub *cub,
													t_pic *texture, t_ray *ray);

int						create_bitmap(t_pic *img, char *name);
int						event_destroy_window(void *param);

#endif
