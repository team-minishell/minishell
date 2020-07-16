/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:43:26 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:19:59 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	print_flag(t_struct *ptr, int output_len)
{
	int i;

	i = 0;
	if (!ptr->zero)
	{
		while (i < (ptr->width - output_len))
		{
			pf_putchar(' ', ptr);
			i++;
		}
	}
	if (ptr->zero)
	{
		while (i < (ptr->width - output_len))
		{
			pf_putchar('0', ptr);
			i++;
		}
	}
}
