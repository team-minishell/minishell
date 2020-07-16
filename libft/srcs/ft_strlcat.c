/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:22:23 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 02:25:50 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	while (i + dest_len + 1 < size && src[i] != '\0')
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
	return (dest_len + src_len);
}
