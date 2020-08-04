/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:05:30 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 03:10:02 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1 + i);
	if (j)
		while (s1[j + i - 1] != 0 && ft_strchr(set, s1[j + i - 1]) != 0)
			j--;
	if (!(str = malloc(sizeof(char) * j + 1)))
		return (NULL);
	ft_strlcpy(str, s1 + i, j + 1);
	str[j] = '\0';
	return (str);
}
