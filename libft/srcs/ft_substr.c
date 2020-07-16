/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:15:03 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/13 17:48:06 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (0);
	i = 0;
	while (i < len && s[i + start] != 0)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
