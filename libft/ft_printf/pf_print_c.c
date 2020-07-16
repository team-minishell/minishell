/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:25:21 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:19:25 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	print_c(t_struct *ptr)
{
	char c;

	c = va_arg(ptr->ap, int);
	if (!ptr->minus)
	{
		print_flag(ptr, 1);
		pf_putchar(c, ptr);
	}
	else if (ptr->minus)
	{
		pf_putchar(c, ptr);
		print_flag(ptr, 1);
	}
	reset_struct(ptr);
}
