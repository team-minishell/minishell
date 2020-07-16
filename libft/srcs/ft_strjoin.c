/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:59:22 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/13 08:49:30 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (0);
	while (*(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j) != '\0')
	{
		*(str + i) = *(s2 + j);
		i++;
		j++;
	}
	*(str + i) = '\0';
	return (str);
}
