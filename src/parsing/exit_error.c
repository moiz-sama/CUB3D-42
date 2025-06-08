/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:13:28 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/08 15:53:39 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	str_len(char **str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

void	str_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_data(t_parse *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(data->textures_paths[i]);
		i++;
	}
	if (data->map2d)
		str_free(data->map2d);
	get_next_line(1, 1);
}

void	ft_error(char *err, char **str, char *line, t_parse *data)
{
	if (data)
		free_data(data);
	if (str)
		str_free(str);
	free(line);
	write(2, "Error : ", 8);
	if (err)
		write(2, err, ft_strlen(err));
	exit (EXIT_FAILURE);
}
