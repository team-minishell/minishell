/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:11:07 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:21:43 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	print_s(t_struct *ptr)
{
	char	*str;
	int		len;

	str = va_arg(ptr->ap, char *);
	if (!str)
		str = "(null)";
	len = pf_strlen(str);
	if (ptr->dot)
		if (len > ptr->precision)
			len = ptr->precision;
	if (ptr->zero == true && ptr->minus == true)
		ptr->zero = false;
	if (!ptr->minus)
	{
		print_flag(ptr, len);
		pf_putstr(str, ptr);
	}
	else if (ptr->minus)
	{
		pf_putstr(str, ptr);
		print_flag(ptr, len);
	}
	reset_struct(ptr);
}
