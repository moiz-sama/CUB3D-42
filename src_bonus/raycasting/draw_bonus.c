/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:55:41 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/11 01:34:28 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	draw_wall(t_img *img, t_ray *ray, int x, t_data *data)
{
	int	start;
	int	end;
	int	i;

	start = (WIN_HEIGHT - ray->height) / 2;
	end = start + ray->height;
	if (end > WIN_HEIGHT)
		end = WIN_HEIGHT;
	i = -1;
	while (++i < start)
		my_pixel_put(img, x, i, data->ceiling_color);
	i = -1;
	if (start > 0)
		i = start - 1;
	while (++i < end)
	{
		get_texture_color(data, ray, i - start);
		my_pixel_put(img, x, i, ray->curr_color);
	}
	while (i < WIN_HEIGHT)
		my_pixel_put(img, x, i++, data->floor_color);
}

int	get_tile_color(t_data *data, int x, int y)
{
	if (y < 0 || x < 0 || y >= data->map_height || x >= data->map_width)
		return (GRAY);
	if (data->map2d[y] && data->map2d[y][x] == '1')
		return (WHITE);
	if (data->map2d[y][x] == '0' || data->map2d[y][x] == ' '
		|| data->map2d[y][x] == 'N' || data->map2d[y][x] == 'S'
		|| data->map2d[y][x] == 'E' || data->map2d[y][x] == 'W')
		return (BLACK);
	return (GRAY);
}

void	draw_map(t_data *data)
{
	int	y;
	int	x;
	int	y_;
	int	x_;
	int	color;

	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			y_ = ((data->player_y / TILE_SIZE) - (SIZE_Y / 2)) + y;
			x_ = ((data->player_x / TILE_SIZE) - (SIZE_X / 2)) + x;
			color = get_tile_color(data, x_, y_);
			draw_tile(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player_rays(t_img *img, t_player_draw_vars *vars)
{
	int		i;
	double	next_x;
	double	next_y;

	while (vars->ray_angle < vars->end_ray_angle)
	{
		i = 1;
		while (i < 7)
		{
			next_x = vars->mini_player_x + (cos(d2rad(vars->ray_angle)) * i);
			next_y = vars->mini_player_y + (sin(d2rad(vars->ray_angle)) * i);
			my_pixel_put(img, (int)next_x, (int)next_y, RED);
			i++;
		}
		vars->ray_angle += 0.3;
	}
}

void	draw_player(t_img *img, int x, int y, t_data *data)
{
	t_player_draw_vars	vars;
	int					start[2];

	(void)x;
	(void)y;
	vars.mini_player_x = SIZE_X / 2 * MINI_MAP_SIZE;
	vars.mini_player_y = SIZE_Y / 2 * MINI_MAP_SIZE;
	vars.ray_angle = data->player_angle - 30;
	vars.end_ray_angle = data->player_angle + 30;
	start[0] = (int)vars.mini_player_x;
	start[1] = (int)vars.mini_player_y;
	draw_square(img, start, 2, RED);
	draw_player_rays(img, &vars);
}
