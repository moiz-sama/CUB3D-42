/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:09:46 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 17:43:33 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	top_bottom_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	player_space_border_check(t_parse *data, int y, int x, char c)
{
	int		flag;
	char	*set;
	char	**map;

	flag = 0;
	map = data->map2d;
	set = " 1";
	if (c == 'p')
		set = "10";
	if (map[y][x + 1] && !ft_strchr(set, map[y][x + 1]))
		flag = 1;
	else if (x > 0 && !ft_strchr(set, map[y][x - 1]))
		flag = 1;
	else if (y > 0 && (int)ft_strlen(map[y - 1]) >= x
		&& !ft_strchr(set, map[y - 1][x]))
		flag = 1;
	else if (map[y + 1] && (int)ft_strlen(map[y + 1]) >= x
		&& !ft_strchr(set, map[y + 1][x]))
		flag = 1;
	if (flag)
		ft_error("map isn't surrounded by walls\n", NULL, NULL, data);
}

void	set_player_angle(t_parse *data, char player_char, int y, int x)
{
	if (data->player_angle != -1)
		ft_error("duplicate player character in the map\n", NULL, NULL, data);
	if (player_char == 'N')
		data->player_angle = N_ANGLE;
	else if (player_char == 'W')
		data->player_angle = W_ANGLE;
	else if (player_char == 'E')
		data->player_angle = E_ANGLE;
	else if (player_char == 'S')
		data->player_angle = S_ANGLE;
	player_space_border_check(data, y, x, 'p');
}

void	map_pars_helper(char **map, int y, int x, t_parse *data)
{
	if (!ft_strchr(" 01NSWE", map[y][x]))
		ft_error("use of invalid character in the map\n", NULL, NULL, data);
	if (ft_strchr("SNWE", map[y][x]))
		set_player_angle(data, map[y][x], y, x);
	if (map[y][x] == '0' && ((int)ft_strlen(map[y - 1]) <= x
		|| (int)ft_strlen(map[y + 1]) <= x))
		ft_error("map isn't surrounded by walls\n", NULL, NULL, data);
	if (map[y][x] == ' ')
		player_space_border_check(data, y, x, ' ');
}

void	map_parser(char **map, t_parse *data)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		if ((y == 0 || !map[y + 1]) && top_bottom_check(map[y]))
			ft_error("map isn't surrounded by walls", NULL, NULL, data);
		while (map[y][++x])
		{
			if ((x == 0 || x == (int)ft_strlen(map[y]) - 1)
				&& !ft_strchr(" 1", map[y][x]))
				ft_error("map isn't surrounded by walls", NULL, NULL, data);
			map_pars_helper(map, y, x, data);
			if (x > data->map_width)
				data->map_width = x + 1;
		}
	}
	if (data->player_angle == -1)
		ft_error("player not found in the map\n", NULL, NULL, data);
}
