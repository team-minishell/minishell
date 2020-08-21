/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:14:46 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/21 18:02:46 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_cd(t_command *command)
{
	int		len;
	t_dict	*home;

	home = find_env(g_env->envd, "HOME");
	len = ft_split_len(command->argv);
	if (len == 1)
	{
		chdir(home->value);
		g_status = 0;
		return (0);
	}
	if (chdir(command->argv[1]))
	{
		ft_putstr_fd("cd: ", 2);
		ft_perror(command->argv[1], errno);
	}
	g_status = 0;
	return (0);
}
