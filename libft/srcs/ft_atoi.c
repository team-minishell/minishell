/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:48:39 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/18 05:51:29 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int i;
	int result_num;
	int minus;

	i = 0;
	result_num = 0;
	minus = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result_num *= 10;
		result_num += nptr[i] - '0';
		i++;
	}
	return (minus == 0 ? result_num : -result_num);
}
