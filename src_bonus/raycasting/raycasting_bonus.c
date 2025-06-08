/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:27:17 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 22:31:52 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_raycasting_info(x, &ray, data);
		set_dda(&ray, data);
		perform_dda(&ray, data);
		calculate_line_height(&ray, data);
		draw_wall(&data->img, &ray, x, data);
		x++;
	}
	return (0);
}

int	render(void *ptr)
{
	t_data	*data;

	data = ptr;
	player_move(data, data->map2d);
	raycasting(data);
	draw_map(data);
	draw_player(&data->img, data->player_x, data->player_y, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}
