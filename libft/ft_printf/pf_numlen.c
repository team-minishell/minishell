/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:33:31 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:12:05 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int		pf_numlen(int num)
{
	int i;

	i = 0;
	while (num / 10)
	{
		num /= 10;
		i++;
	}
	return (++i);
}

int		if_minus(int i, const char *str, t_struct *ptr)
{
	if (str[i] == '-')
		ptr->minus = true;
	else if (str[i] == '0')
		ptr->zero = true;
	while (str[i] == '-' || str[i] == '0')
	{
		if (str[i + 1] != '0' && is_nbr(str, i + 1))
			break ;
		i++;
	}
	return (i);
}
