/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 23:53:03 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/13 17:59:51 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	bool			occured;
	unsigned char	*usrc;

	usrc = (unsigned char *)src;
	i = 0;
	occured = 0;
	while (i < n && usrc[i] && !occured)
	{
		occured = ((usrc)[i] == (unsigned char)c) ? 1 : 0;
		i++;
	}
	if (occured)
	{
		ft_memcpy(dst, usrc, i);
		return (dst + i);
	}
	else
	{
		ft_memcpy(dst, usrc, n);
		return (0);
	}
}
