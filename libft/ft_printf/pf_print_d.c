/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:18:23 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:19:44 by yochoi           ###   ########.fr       */
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

static void	print_d2(t_struct *ptr, char *str, int len, bool minus)
{
	int output_len;

	output_len = zero_precision(ptr, len) + minus;
	if (!ptr->minus)
	{
		if (minus && ptr->zero == true)
			pf_putchar('-', ptr);
		print_flag(ptr, output_len);
		if (minus && ptr->zero == false)
			pf_putchar('-', ptr);
		print_precision(ptr, len);
		pf_putstr(str, ptr);
	}
	else if (ptr->minus)
	{
		if (minus)
			pf_putchar('-', ptr);
		print_precision(ptr, len);
		pf_putstr(str, ptr);
		print_flag(ptr, output_len);
	}
	reset_struct(ptr);
	return (free(str));
}

static void	print_exception(t_struct *ptr)
{
	int			output_len;
	const char	*str = "2147483648";

	if (ptr->dot == true && ptr->zero == true)
		ptr->zero = false;
	output_len = zero_precision(ptr, 11);
	if (!ptr->minus)
	{
		if (ptr->zero == true)
			pf_putchar('-', ptr);
		print_flag(ptr, output_len);
		if (ptr->zero == false)
			pf_putchar('-', ptr);
		print_precision(ptr, 11);
		pf_putstr(str, ptr);
	}
	else if (ptr->minus)
	{
		pf_putchar('-', ptr);
		print_precision(ptr, 11);
		pf_putstr(str, ptr);
		print_flag(ptr, output_len);
	}
	reset_struct(ptr);
}

void		print_d(t_struct *ptr)
{
	int		len;
	int		num;
	char	*str;
	bool	minus;

	minus = false;
	num = va_arg(ptr->ap, int);
	if (num == -2147483648)
		return (print_exception(ptr));
	if (num < 0)
	{
		minus = true;
		num *= -1;
	}
	str = pf_itoa(num);
	len = pf_strlen(str);
	if (ptr->dot == true && ptr->zero == true)
		ptr->zero = false;
	if (str[0] == '0' && ptr->precision == 0 && ptr->dot == true)
	{
		print_flag(ptr, (zero_precision(ptr, len) + minus - 1));
		reset_struct(ptr);
		return (free(str));
	}
	print_d2(ptr, str, len, minus);
}
