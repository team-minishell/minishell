/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:22:49 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:13:10 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void		pf_putnbr(int n, t_struct *ptr)
{
	char	*num;
	int		num_len;
	int		i;

	if (n == 0 && ptr->precision == 0)
	{
		reset_struct(ptr);
		return ;
	}
	i = 0;
	num = pf_itoa_base(n, 10, 'a');
	num_len = pf_strlen(num);
	if (num_len < ptr->precision)
		while (i++ < (ptr->precision - num_len))
			pf_putchar('0', ptr);
	else
	{
		ptr->dot = false;
		ptr->precision = 0;
	}
	pf_putstr(num, ptr);
	free(num);
}

void		pf_put_unbr(unsigned int n, t_struct *ptr)
{
	char	*num;
	int		num_len;
	int		i;

	if (n == 0 && ptr->precision == 0)
	{
		reset_struct(ptr);
		return ;
	}
	i = 0;
	num = pf_itoa_base((int)n, 10, 'a');
	num_len = pf_strlen(num);
	if (num_len < ptr->precision)
		while (i++ < (ptr->precision - num_len))
			pf_putchar('0', ptr);
	else
	{
		ptr->dot = false;
		ptr->precision = 0;
	}
	pf_putstr(num, ptr);
	free(num);
}
