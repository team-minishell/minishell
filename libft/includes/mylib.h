/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:57:04 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:11:16 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIB_H
# define MYLIB_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct	s_struct
{
	const char	*format;
	va_list		ap;
	int			len;
	bool		minus;
	bool		zero;
	int			width;
	int			dot;
	int			precision;
}				t_struct;

void			reset_struct(t_struct *ptr);

int				is_specifier(const char *str, int i);

int				is_nbr(const char *str, int i);

int				if_minus(int i, const char *str, t_struct *ptr);

void			read_str(t_struct *ptr);

void			print_d(t_struct *ptr);

void			print_s(t_struct *ptr);

void			print_c(t_struct *ptr);

void			print_p(t_struct *ptr);

void			print_u(t_struct *ptr);

void			print_small_x(t_struct *ptr);

void			print_big_x(t_struct *ptr);

void			print_percent(t_struct *ptr);

void			pf_putchar(char c, t_struct *ptr);

size_t			pf_strlen(const char *s);

char			*pf_strdup(char *s);

char			*pf_strnew(size_t size);

void			*pf_memset(void *b, int c, size_t len);

void			pf_bzero(void *s, size_t n);

char			*pf_itoa_base(size_t num, size_t base, char c);

char			*pf_itoa_base_u(unsigned int num, unsigned int base, char c);

char			*pf_itoa(int n);

char			*pf_itoa_t(unsigned int n);

void			pf_putstr(const char *s, t_struct *ptr);

void			pf_putstr_p(char *s, t_struct *ptr);

void			pf_puthex(char *hexadecimal, t_struct *ptr);

void			pf_putnbr(int n, t_struct *ptr);

void			check_format(const char *str, t_struct *ptr, int i);

int				check_flag(const char *str, t_struct *ptr, int i);

int				pf_numlen(int num);

void			pf_put_unbr(unsigned int n, t_struct *ptr);

void			print_flag(t_struct *ptr, int output_len);
#endif
