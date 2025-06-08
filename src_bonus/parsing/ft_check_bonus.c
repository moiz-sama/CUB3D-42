/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:39:05 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/09 20:10:52 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	set_hight_width(t_parse *data)
{
	int	i;

	i = 0;
	while (data->map2d[i])
	{
		data->map_height++;
		if ((int)ft_strlen(data->map2d[i]) > data->map_width)
			data->map_width = ft_strlen(data->map2d[i]);
		i++;
	}
}

void	open_file_texture(char *file, t_parse *data, char *line, int i)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error : can't open file texture -> ", 35);
		printf("%s\n", data->textures_paths[i]);
		free_data(data);
		free(line);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return ;
}

void	check_texture_and_color(t_parse *data, char *line)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		if (!data->textures_paths[i])
			ft_error("missing textures path\n", NULL, line, data);
		open_file_texture(data->textures_paths[i], data, line, i);
		i++;
	}
	if (data->ceiling_color == -1)
		ft_error("missing ceiling color\n", NULL, line, data);
	if (data->floor_color == -1)
		ft_error("missing floor color\n", NULL, line, data);
}
