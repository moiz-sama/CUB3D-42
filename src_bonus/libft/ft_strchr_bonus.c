/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <saderdou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:42:59 by saderdou          #+#    #+#             */
/*   Updated: 2025/02/28 22:37:18 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)str;
	while (ptr[i])
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	if (ptr[i] == (unsigned char)c)
		return (&ptr[i]);
	return (NULL);
}
