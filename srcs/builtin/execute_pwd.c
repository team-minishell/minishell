/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:26 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/14 19:29:17 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_pwd(t_command *command)
{
	char	buf[1024];
	int		len;

	len = ft_split_len(command->argv);
	if (len != 1)
	{
		ft_printf("pwd: too many arguments\n");
		return (1);
	}
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	ft_printf("%s\n", buf);
	return (0);
}
