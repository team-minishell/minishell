/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 16:43:33 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 18:11:38 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static int			num_size(long n)
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

static unsigned int	num_size_t(unsigned int n)
{
	unsigned int size;

	size = 1;
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char				*pf_itoa(int n)
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

char				*pf_itoa_t(unsigned int n)
{
	char				*str;
	unsigned int		i;

	i = num_size_t(n);
	if (!(str = (char *)malloc(sizeof(char) * num_size_t(n) + 1)))
		return (0);
	i[str] = '\0';
	i--;
	while (i > 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	str[i] = n + '0';
	return (str);
}
