/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 22:37:20 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 18:12:56 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	pf_puthex(char *hexadecimal, t_struct *ptr)
{
	int		num_len;
	int		i;

	if (hexadecimal == 0)
		hexadecimal = pf_strdup("0");
	if (ptr->precision == 0 && ptr->dot == true)
		return (free(hexadecimal));
	i = 0;
	num_len = pf_strlen(hexadecimal);
	if (num_len < ptr->precision)
		while (i++ < (ptr->precision - num_len))
			pf_putchar('0', ptr);
	else
	{
		ptr->dot = false;
		ptr->precision = 0;
	}
	pf_putstr(hexadecimal, ptr);
	return (free(hexadecimal));
}
