/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_raycasting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:28:04 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/15 08:03:07 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	set_dda(t_ray *ray, t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player_x / TILE_SIZE;
	pos_y = data->player_y / TILE_SIZE;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map2d[ray->map_y]
			&& data->map2d[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calculate_line_height(t_ray *ray, t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player_x / TILE_SIZE;
	pos_y = data->player_y / TILE_SIZE;
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	ray->wall_dist *= TILE_SIZE;
	ray->line_height = (int)(TILE_SIZE * WIN_HEIGHT) / ray->wall_dist;
	ray->draw_start = (WIN_HEIGHT / 2) - (ray->line_height / 2) + (WIN_HEIGHT
			/ 8);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (WIN_HEIGHT / 2) + (ray->line_height / 2) + (WIN_HEIGHT
			/ 8);
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	set_wall_hit_xy(ray, data);
}
