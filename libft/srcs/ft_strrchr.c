/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:37:23 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 02:40:37 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = ft_strlen(s);
	ret = (char *)s;
	while (i >= 0)
	{
		if (s[i] == c && c != '\n')
			return (&ret[i]);
		i--;
	}
	return (NULL);
}
