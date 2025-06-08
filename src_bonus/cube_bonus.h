/* ************************************************************************** */
/*				                                                              */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:48:42 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:21 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

# include "parsing/parse_bonus.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>

# define PI 3.141592653589793
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define TILE_SIZE 100
# define MINI_MAP_SIZE 5
# define FOV 0.60
# define PLAYER_SPEED 10
# define ANGLE_AC 1
# define SIZE_Y 30
# define SIZE_X 50

# define N_INDEX 0
# define S_INDEX 1
# define W_INDEX 2
# define E_INDEX 3

typedef struct s_img
{
	void		*img_ptr;
	char		*img_pixels_ptr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_texture
{
	void		*img;
	char		*iter;
	int			line_length;
	int			pixel_bits;
	int			endianess;
	int			width;
	int			hight;
}				t_texture;

typedef struct s_player_draw_vars
{
	double		mini_player_x;
	double		mini_player_y;
	double		ray_angle;
	double		end_ray_angle;
}				t_player_draw_vars;

typedef struct s_data
{
	char		**map2d;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	double		player_x;
	double		player_y;
	double		player_angle;
	t_texture	wall_textures[4];
	t_img		img;
	void		*mlx;
	void		*win;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_l;
	int			key_r;
}				t_data;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_idx;
	int			curr_color;
	int			height;
	double		wall_hit_x;
	double		wall_hit_y;
}				t_ray;

double			d2rad(double d);
void			my_pixel_put(t_img *img, int x, int y, int color);
int				player_move(t_data *data, char *map_data[]);
void			init_raycasting_info(int x, t_ray *ray, t_data *data);
void			set_dda(t_ray *ray, t_data *data);
void			perform_dda(t_ray *ray, t_data *data);
void			calculate_line_height(t_ray *ray, t_data *data);
void			draw_wall(t_img *img, t_ray *ray, int x, t_data *data);
int				raycasting(t_data *data);
int				render(void *ptr);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			int_data(t_data *data, t_parse *parse);
int				mouse_move_hook(int x, int y, t_data *data);
void			draw_map(t_data *data);
void			draw_player(t_img *img, int x, int y, t_data *data);
void			draw_square(t_img *img, int start[2], int size, int color);
void			draw_tile(t_data *data, int x, int y, int color);

// texture
void			set_wall_hit_xy(t_ray *ray, t_data *data);
void			get_texture_color(t_data *data, t_ray *ray, int current_y);
void			initialize_textures(t_data *data, t_parse *parse);
void			free_textures(void *mlx, t_texture *textures);

// colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GRAY 0x808080
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define BROWN 0xA52A2A
# define LIGHT_GRAY 0xD3D3D3
# define DARK_GREEN 0x006400
# define LIGHT_PINK 0xFFB6C1

#endif