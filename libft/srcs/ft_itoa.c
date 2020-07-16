/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:19:51 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 04:29:36 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		num_size(long n)
{
	int size;

	size = 1;
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		i;

	i = 0;
	num = n;
	if (!(str = (char *)malloc(sizeof(char) * num_size(n) + 1)))
		return (0);
	if (n < 0)
	{
		num *= -1;
		i++;
	}
	i += num_size(num);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	if (n < 0)
		str[i + 1] = '-';
	return (str);
}
