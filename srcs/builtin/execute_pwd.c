/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:26 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/06 23:38:54 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_pwd(t_job *job)
{
	char	buf[1024];
	int		len;

	len = ft_split_len(job->command->argv);
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