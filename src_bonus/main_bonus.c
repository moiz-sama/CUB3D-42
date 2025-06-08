/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:44:45 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/11 01:10:42 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

int	handle_keys(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	free_textures(data->mlx, data->wall_textures);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	str_free(data->map2d);
	exit(0);
}

void	start_cube(t_parse *parse)
{
	t_data	data;

	int_data(&data, parse);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "CUBE3D");
	data.img.img_ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.img.img_pixels_ptr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
	initialize_textures(&data, parse);
	parse->map2d = NULL;
	free_data(parse);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, mouse_move_hook, &data);
	mlx_hook(data.win, 17, 0, handle_keys, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}

int	main(int ac, char **av)
{
	t_parse	data;

	if (ac != 2)
		return (printf("error usage : ./cub3d file.cub\n"), EXIT_FAILURE);
	start_parsing(&data, av);
	start_cube(&data);
}
