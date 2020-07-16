/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:58 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/12 09:41:01 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (!(str = ft_calloc(sizeof(char), ft_strlen(s) + 1)))
		return (0);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
