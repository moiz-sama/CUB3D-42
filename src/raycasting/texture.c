/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:51:46 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/11 02:20:27 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	initialize_textures(t_data *data, t_parse *parse)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(
				data->mlx,
				parse->textures_paths[i],
				&data->wall_textures[i].width,
				&data->wall_textures[i].hight);
		if (!data->wall_textures[i].img)
			ft_error("texture fail\n", NULL, NULL, parse);
		data->wall_textures[i].iter = mlx_get_data_addr(
				data->wall_textures[i].img,
				&data->wall_textures[i].pixel_bits,
				&data->wall_textures[i].line_length,
				&data->wall_textures[i].endianess);
		i++;
	}
}

void	set_wall_hit_xy(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		ray->wall_hit_x = ray->map_x;
		if (ray->step_x == 1)
			ray->wall_hit_x += 1;
		ray->wall_hit_y = data->player_y + ray->ray_dir_y * ray->wall_dist;
		if (ray->step_x == 1)
			ray->texture_idx = E_INDEX;
		else
			ray->texture_idx = W_INDEX;
	}
	else
	{
		ray->wall_hit_x = data->player_x + ray->ray_dir_x * ray->wall_dist;
		ray->wall_hit_y = ray->map_y;
		if (ray->step_y == 1)
			ray->wall_hit_y += 1;
		if (ray->step_y == 1)
			ray->texture_idx = S_INDEX;
		else
			ray->texture_idx = N_INDEX;
	}
	ray->height = ((float)TILE_SIZE / ray->wall_dist)
		* ((float)WIN_WIDTH / 2) / tan(radian(60 / 2));
}

static int	get_cords_color(t_texture *img, int x, int y)
{
	char	*dst;
	int		offset;

	if (!img || !img->iter)
	{
		printf("Error: Invalid texture data\n");
		return (0);
	}
	offset = (y * img->line_length + x * (img->pixel_bits / 8));
	if (offset < 0)
		return (0);
	dst = img->iter + offset;
	return (*(unsigned int *)dst);
}

void	get_texture_color(t_data *data, t_ray *ray, int current_y)
{
	float	x_scale;
	float	y_scale;
	int		current_x;

	current_x = 0;
	x_scale = (float)data->wall_textures[ray->texture_idx].width / TILE_SIZE;
	y_scale = (float)data->wall_textures[ray->texture_idx].hight / ray->height;
	if (ray->texture_idx == N_INDEX)
		current_x = (int)ray->wall_hit_x % TILE_SIZE;
	else if (ray->texture_idx == S_INDEX)
		current_x = TILE_SIZE - ((int)ray->wall_hit_x % TILE_SIZE);
	else if (ray->texture_idx == E_INDEX)
		current_x = (int)ray->wall_hit_y % TILE_SIZE;
	else if (ray->texture_idx == W_INDEX)
		current_x = TILE_SIZE - ((int)ray->wall_hit_y % TILE_SIZE);
	ray->curr_color = get_cords_color(&data->wall_textures[ray->texture_idx],
			current_x * x_scale, current_y * y_scale);
}
