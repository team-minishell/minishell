/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 21:46:00 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/17 21:46:30 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if ((str = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	ft_memset(str, (int)'\0', size + 1);
	return (str);
}
