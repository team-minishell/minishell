/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 22:08:35 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 18:21:27 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	print_percent(t_struct *ptr)
{
	if (ptr->zero == true && ptr->minus == true)
		ptr->zero = false;
	if (!ptr->minus)
	{
		print_flag(ptr, 1);
		pf_putchar('%', ptr);
	}
	else if (ptr->minus)
	{
		pf_putchar('%', ptr);
		print_flag(ptr, 1);
	}
	reset_struct(ptr);
}
