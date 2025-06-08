/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:55:41 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 18:56:08 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
