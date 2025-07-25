/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:29 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 22:31:52 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	words_cnt(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

char	**ft_free(char **str, int i)
{
	while (i > 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	*ft_fill(char *ptr, char const *s, int j, int wl)
{
	int	i;

	i = 0;
	while (wl > 0)
	{
		ptr[i] = s[j - wl];
		i++;
		wl--;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**split_words(char const *s, char **str, char c, int wc)
{
	int	i;
	int	word;
	int	wl;

	i = 0;
	word = 0;
	wl = 0;
	while (word < wc)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			wl++;
			i++;
		}
		str[word] = (char *)malloc(sizeof(char) * (wl + 1));
		if (!str[word])
			return (ft_free(str, word));
		ft_fill(str[word], s, i, wl);
		wl = 0;
		word++;
	}
	str[word] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**str;

	wc = 0;
	if (!s)
		return (NULL);
	wc = words_cnt(s, c);
	str = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!str)
		return (NULL);
	str = split_words(s, str, c, wc);
	return (str);
}
