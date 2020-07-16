/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:13:42 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:23:11 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static void	print_precision(t_struct *ptr, int len)
{
	int		i;

	i = 0;
	if (len < ptr->precision)
		while (i++ < (ptr->precision - len))
			pf_putchar('0', ptr);
	ptr->dot = false;
	ptr->precision = 0;
	return ;
}

static int	zero_precision(t_struct *ptr, int len)
{
	int		i;
	int		ret;

	i = 0;
	ret = len;
	if (len < ptr->precision)
		while (i++ < (ptr->precision - len))
			ret++;
	return (ret);
}

static void	print_d2(t_struct *ptr, char *str, int len)
{
	int output_len;

	output_len = zero_precision(ptr, len);
	if (!ptr->minus)
	{
		print_flag(ptr, output_len);
		print_precision(ptr, len);
		pf_putstr(str, ptr);
	}
	else if (ptr->minus)
	{
		print_precision(ptr, len);
		pf_putstr(str, ptr);
		print_flag(ptr, output_len);
	}
	reset_struct(ptr);
	return (free(str));
}

void		print_u(t_struct *ptr)
{
	int		len;
	int		num;
	char	*str;

	num = va_arg(ptr->ap, unsigned int);
	str = pf_itoa_t(num);
	len = pf_strlen(str);
	if (str[0] == '0' && ptr->precision == 0 && ptr->dot == true)
	{
		if (ptr->dot == true && ptr->zero == true)
			ptr->zero = false;
		print_flag(ptr, zero_precision(ptr, 0));
		reset_struct(ptr);
		return (free(str));
	}
	if (ptr->dot == true && ptr->zero == true)
		ptr->zero = false;
	print_d2(ptr, str, len);
}
