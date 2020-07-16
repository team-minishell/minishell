/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:52:31 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 00:57:16 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (!(ptr = (void *)malloc(nmemb * size)))
		return (0);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
