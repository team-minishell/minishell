/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:14:30 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:21:15 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void		print_p(t_struct *ptr)
{
	unsigned long	num;
	char			*str;
	int				len;

	num = va_arg(ptr->ap, unsigned long);
	str = pf_itoa_base(num, 16, 'a');
	if (num == 0 && ptr->dot == false)
		len = 3;
	else if (num == 0 && ptr->dot == true)
		len = 2;
	else
		len = pf_strlen(str) + 2;
	if (!ptr->minus)
	{
		print_flag(ptr, len);
		pf_putstr_p(str, ptr);
	}
	else if (ptr->minus)
	{
		pf_putstr_p(str, ptr);
		print_flag(ptr, len);
	}
	reset_struct(ptr);
	return (free(str));
}
