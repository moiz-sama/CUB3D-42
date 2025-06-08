/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:59:59 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/15 07:52:32 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	rgb_check(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] == '0' || str[i] == ' ')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			len++;
		else if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	if (len > 3)
		return (1);
	if (ft_atoi(str) > 255)
		return (1);
	return (0);
}

int	nb(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == ',')
			nb++;
		i++;
	}
	return (nb);
}

void	color_parser(t_parse *data, char *line, char **words)
{
	char	*color;
	int		i;
	char	**rgb;

	if (str_len(words) != 2)
		ft_error("syntax error color\n", words, line, data);
	i = -1;
	color = (char *)&data->floor_color;
	if (!ft_strncmp(words[0], "C", 2))
		color = (char *)&data->ceiling_color;
	if (*color != -1)
		ft_error("duplicate type element\n", words, line, data);
	rgb = ft_split(line + 1, ',');
	if (str_len(rgb) != 3 || nb(words[1]) != 2)
		return (str_free(rgb), ft_error("color must be in format R,G,B\n",
				words, line, data));
	while (++i < 3)
		if (rgb_check(rgb[i]) != 0)
			return (str_free(rgb), ft_error("colors must be in range [0,255]\n",
					words, line, data));
	while (--i >= 0)
		*color++ = ft_atoi(rgb[i]);
	*color = 0;
	str_free(rgb);
}

int	find_double_newline(const char *str)
{
	int	len;
	int	i;

	len = strlen(str);
	i = 0;
	while (i < len - 1)
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
