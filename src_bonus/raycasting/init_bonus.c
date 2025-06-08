/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:21:57 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 22:31:52 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	int_data(t_data *data, t_parse *parse)
{
	data->map2d = parse->map2d;
	data->map_height = parse->map_height;
	data->map_width = parse->map_width;
	data->ceiling_color = parse->ceiling_color;
	data->floor_color = parse->floor_color;
	data->player_angle = parse->player_angle;
	data->player_x = parse->player_x;
	data->player_y = parse->player_y;
	data->map_width = parse->map_width;
	data->map_height = parse->map_height;
	data->key_w = 0;
	data->key_a = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_l = 0;
	data->key_r = 0;
}

void	init_raycasting_info(int x, t_ray *ray, t_data *data)
{
	ray->camera_x = (2 * x / (double)WIN_WIDTH - 1);
	ray->dir_x = cos(d2rad(data->player_angle));
	ray->dir_y = sin(d2rad(data->player_angle));
	ray->plane_x = -ray->dir_y * FOV;
	ray->plane_y = ray->dir_x * FOV;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)(data->player_x / TILE_SIZE);
	ray->map_y = (int)(data->player_y / TILE_SIZE);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}
