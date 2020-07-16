/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:20:23 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:10:33 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void		check_format(const char *str, t_struct *ptr, int i)
{
	if (str[i] == 'd' || str[i] == 'i')
		print_d(ptr);
	if (str[i] == 's')
		print_s(ptr);
	if (str[i] == 'c')
		print_c(ptr);
	if (str[i] == 'x')
		print_small_x(ptr);
	if (str[i] == 'X')
		print_big_x(ptr);
	if (str[i] == 'p')
		print_p(ptr);
	if (str[i] == 'u')
		print_u(ptr);
	if (str[i] == '%')
		print_percent(ptr);
}

static int	reverse_width(t_struct *ptr, int i)
{
	if (ptr->width < 0)
	{
		if (ptr->zero == false)
		{
			ptr->minus = true;
			ptr->width *= -1;
		}
		else if (ptr->zero == true)
		{
			ptr->zero = false;
			ptr->minus = true;
			ptr->width *= -1;
		}
	}
	i += 1;
	return (i);
}

static int	check_flag2(const char *str, t_struct *ptr, int i)
{
	if (str[i] == '.')
	{
		ptr->dot = true;
		i++;
	}
	if (str[i] == '*')
	{
		ptr->precision = va_arg(ptr->ap, int);
		i++;
	}
	while (is_nbr(str, i))
	{
		ptr->precision *= 10;
		ptr->precision += str[i] - '0';
		i++;
	}
	if (ptr->precision < 0)
	{
		ptr->dot = false;
		ptr->precision = 0;
	}
	return (i);
}

static int	width_check(const char *str, t_struct *ptr, int i)
{
	bool minus;

	minus = false;
	if (str[i] == '-')
	{
		i++;
		minus = true;
	}
	while (is_nbr(str, i))
	{
		ptr->width *= 10;
		ptr->width += str[i] - '0';
		i++;
	}
	if (minus)
		ptr->width *= -1;
	return (i);
}

int			check_flag(const char *str, t_struct *ptr, int i)
{
	if (str[i] == '-' || str[i] == '0')
		i = if_minus(i, str, ptr);
	if (str[i] == '*' || is_nbr(str, i) || str[i] == '-')
	{
		if (str[i] == '*')
		{
			ptr->width = va_arg(ptr->ap, int);
			i = reverse_width(ptr, i);
		}
		else
		{
			i = width_check(str, ptr, i);
			reverse_width(ptr, i);
		}
	}
	return (check_flag2(str, ptr, i));
}
