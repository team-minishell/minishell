/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:47 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 03:10:15 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	if (!(str = ft_calloc(ft_strlen(s) + 1, sizeof(char))))
		return (0);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(str + i) = *(s + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
