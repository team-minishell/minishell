/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:14:46 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 21:38:50 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_cd(t_job *job)
{
	int		len;
	t_dict	*home;

	home = find_env(g_env->envd, "HOME");
	len = ft_split_len(job->command.argv);
	if (len == 1)
	{
		chdir(home->value);
		return (0);
	}
	chdir(job->command.argv[1]);
	return (0);
}
