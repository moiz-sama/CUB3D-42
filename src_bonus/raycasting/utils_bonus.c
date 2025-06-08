/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:06:48 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/09 19:59:48 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

double	d2rad(double d)
{
	return (d * PI / 180);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	if (y >= 0 && y <= WIN_HEIGHT && x >= 0 && x <= WIN_WIDTH)
	{
		offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
		*((unsigned int *)(img->img_pixels_ptr + offset)) = color;
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key_w = 1;
	if (keycode == XK_a)
		data->key_a = 1;
	if (keycode == XK_d)
		data->key_d = 1;
	if (keycode == XK_s)
		data->key_s = 1;
	if (keycode == XK_Left)
		data->key_l = 1;
	if (keycode == XK_Right)
		data->key_r = 1;
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		free_textures(data->mlx, data->wall_textures);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		str_free(data->map2d);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key_w = 0;
	if (keycode == XK_a)
		data->key_a = 0;
	if (keycode == XK_d)
		data->key_d = 0;
	if (keycode == XK_s)
		data->key_s = 0;
	if (keycode == XK_Left)
		data->key_l = 0;
	if (keycode == XK_Right)
		data->key_r = 0;
	return (0);
}

void	draw_square(t_img *img, int start[2], int size, int color)
{
	int	x;
	int	y;

	y = start[1];
	while (y < start[1] + size)
	{
		x = start[0];
		while (x < start[0] + size)
		{
			my_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
