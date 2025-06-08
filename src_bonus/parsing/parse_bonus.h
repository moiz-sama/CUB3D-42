/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:41:31 by saderdou          #+#    #+#             */
/*   Updated: 2025/03/15 07:54:06 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "../get_next_line/get_next_line_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define E_ANGLE 0
# define N_ANGLE 270
# define W_ANGLE 180
# define S_ANGLE 90

typedef struct s_parse
{
	char			*textures_paths[4];
	char			**map2d;
	int				floor_color;
	int				ceiling_color;		
	int				map_width;
	int				map_height;
	double			player_x;
	double			player_y;
	double			player_angle;
}	t_parse;

//libft_fts
char	*ft_strchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

//fts_parsing
void	start_parsing(t_parse *data, char **av);
void	line_parse(t_parse *data, char *line, int *flag);
void	is_map_line(char *str, int *flag);
int		str_len(char **str);
void	str_free(char **str);
void	free_data(t_parse *data);
void	ft_error(char *err, char **str, char *line, t_parse *data);
void	color_parser(t_parse *data, char *line, char **words);
void	check_texture_and_color(t_parse *data, char *line);
char	**map_alloc(char *line, int fd, t_parse *data);
void	map_parser(char **map, t_parse *data);
void	set_hight_width(t_parse *data);
void	pad_map_rows(t_parse *data);
int		find_double_newline(const char *str);

#endif