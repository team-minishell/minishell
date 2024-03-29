/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:25:36 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/24 19:46:44 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_already_exist(t_dict *already, char **splits)
{
	ft_strdel(&already->key);
	ft_strdel(&already->value);
	already->key = splits[0];
	already->value = splits[1];
}

void	set_envp(void)
{
	char	**tmp;

	tmp = g_env->envp;
	g_env->envp = make_dict_to_envp(g_env->envd);
	ft_split_del(tmp);
}

int		execute_export(t_command *command)
{
	char	**splits;
	t_dict	*already;
	t_dict	*new;
	t_dict	*dict_tmp;

	if (!command->argv[1])
		return (0);
	splits = ft_split(command->argv[1], '=');
	if ((already = find_env(g_env->envd, splits[0])))
		if_already_exist(already, splits);
	else
	{
		if (!(new = malloc(sizeof(t_dict) * 1)))
			exit(MALLOC_ERROR);
		dict_tmp = g_env->envd;
		g_env->envd = new;
		new->next = dict_tmp;
		new->key = splits[0];
		new->value = splits[1];
		free(splits);
	}
	set_envp();
	g_status = 0;
	return (0);
}
