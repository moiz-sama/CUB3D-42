/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:26:26 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/15 07:40:45 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

static void	update_position(t_data *data, double angle, char *map_data[])
{
	double	next_x;
	double	next_y;
	int		tmp_x;
	int		tmp_y;

	next_x = cos(angle) * PLAYER_SPEED;
	next_y = sin(angle) * PLAYER_SPEED;
	tmp_x = (int)(data->player_x + next_x) / TILE_SIZE;
	tmp_y = (int)(data->player_y + next_y) / TILE_SIZE;
	if (map_data[tmp_y] && map_data[tmp_y][tmp_x] != '1')
	{
		data->player_y += next_y;
		data->player_x += next_x;
	}
}

int	player_move(t_data *data, char *map_data[])
{
	int	d;

	if (data->key_r || data->key_l)
	{
		if (data->key_l)
			data->player_angle -= ANGLE_AC;
		if (data->key_r)
			data->player_angle += ANGLE_AC;
	}
	if (data->key_w || data->key_a || data->key_s || data->key_d)
	{
		d = data->player_angle;
		if (data->key_a && !data->key_s)
			d -= 90;
		if (data->key_d && !data->key_s)
			d += 90;
		if (data->key_s)
			d += 180;
		if (data->key_a && data->key_s)
			d += 90;
		if (data->key_d && data->key_s)
			d -= 90;
		update_position(data, d2rad(d), map_data);
	}
	return (0);
}
