/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:52:10 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/11 02:06:39 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	player_first_coordinates(t_parse *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map2d[++y])
	{
		x = -1;
		while (data->map2d[y][++x])
		{
			if (ft_strchr("NSEW", data->map2d[y][x]))
			{
				data->player_x = (x * TILE_SIZE + TILE_SIZE / 2);
				data->player_y = (y * TILE_SIZE + TILE_SIZE / 2);
				return ;
			}
		}
	}
}

char	**map_alloc(char *line, int fd, t_parse *data)
{
	char	**res;
	char	*new_line;

	new_line = get_next_line(fd, 0);
	while (new_line)
	{
		line = ft_strjoin(line, new_line);
		if (!line)
		{
			free(new_line);
			ft_error("insufficient memory (strjoin)\n", NULL, line, data);
		}
		free(new_line);
		new_line = get_next_line(fd, 0);
	}
	res = ft_split(line, '\n');
	if (!res)
		ft_error("insufficient memory (split)\n", res, line, data);
	return (free(line), res);
}

void	init_data(t_parse *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures_paths[i] = NULL;
		i++;
	}
	data->map2d = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->floor_color = -1;
	data->ceiling_color = -1;
	data->player_angle = -1;
	data->player_x = 0;
	data->player_y = 0;
}

int	open_file(char *av)
{
	int		fd;
	char	*after_dot;

	after_dot = ft_strchr(av, '.');
	if (after_dot == NULL || ft_strlen(av) == 4 || ft_strlen(after_dot) != 4)
		ft_error("invalid file format\n", NULL, NULL, NULL);
	if (ft_strncmp(after_dot, ".cub", 4))
		ft_error("invalid file format\n", NULL, NULL, NULL);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_error("can't open file\n", NULL, NULL, NULL);
	return (fd);
}

void	start_parsing(t_parse *data, char **av)
{
	int		fd;
	char	*str;
	int		flag;

	flag = 0;
	init_data(data);
	fd = open_file(av[1]);
	while (1)
	{
		str = get_next_line(fd, 0);
		if (!str)
			break ;
		line_parse(data, str, &flag);
		if (flag != 0)
			break ;
		free(str);
	}
	if (flag == 0)
		ft_error("there no map in the file\n", NULL, str, data);
	check_texture_and_color(data, str);
	data->map2d = map_alloc(str, fd, data);
	map_parser(data->map2d, data);
	set_hight_width(data);
	pad_map_rows(data);
	player_first_coordinates(data);
}
