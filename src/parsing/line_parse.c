/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:15:34 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/09 13:42:44 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	is_map_line(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '1'))
		*flag = 1;
}

void	get_textures(char **words, t_parse *data, char *line)
{
	int		i;
	char	*tab[5];

	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	tab[4] = NULL;
	i = -1;
	while (tab[++i])
		if (!ft_strncmp(words[0], tab[i], 3))
			break ;
	if (i < 4)
	{
		if (data->textures_paths[i])
			ft_error("duplicate type element\n", words, line, data);
		if (str_len(words) != 2)
			ft_error("syntax error textures\n", words, line, data);
		data->textures_paths[i] = ft_strtrim(words[1], "\n");
		return ;
	}
	if (!ft_strncmp(words[0], "F", 2) || !ft_strncmp(words[0], "C", 2))
		return (color_parser(data, line, words));
	ft_error("unknown element\n", words, line, data);
}

void	line_parse(t_parse *data, char *line, int *flag)
{
	char	**str;

	if (line[0] == '\n')
		return ;
	is_map_line(line, flag);
	if (*flag != 0)
		return ;
	str = ft_split(line, ' ');
	get_textures(str, data, line);
	str_free(str);
}
