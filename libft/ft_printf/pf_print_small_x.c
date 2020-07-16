/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_small_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:45:55 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:22:36 by yochoi           ###   ########.fr       */
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

static void	print_small_x2(t_struct *ptr, int output_len, int len, char *str)
{
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
}

void		print_small_x(t_struct *ptr)
{
	int		num;
	int		len;
	int		output_len;
	char	*str;

	num = va_arg(ptr->ap, int);
	str = pf_itoa_base_u(num, 16, 'a');
	len = pf_strlen(str);
	output_len = zero_precision(ptr, len);
	if (ptr->dot == true && ptr->zero == true)
		ptr->zero = false;
	if (str[0] == '0' && ptr->precision == 0 && ptr->dot == true)
	{
		print_flag(ptr, output_len - 1);
		return (free(str));
	}
	else
		print_small_x2(ptr, output_len, len, str);
	reset_struct(ptr);
	return (free(str));
}
