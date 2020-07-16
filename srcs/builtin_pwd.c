/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:26 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/16 22:18:19 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_pwd(char **tokens)
{
	char	buf[1024];
	int		len;

	len = ft_split_len(tokens);
	if (len != 1)
	{
		ft_printf("pwd: too many arguments\n");
		return (0);
	}
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	ft_printf("%s\n", buf);
	return (1);
}