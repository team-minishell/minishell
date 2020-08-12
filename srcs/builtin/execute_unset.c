/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:26:06 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/12 21:11:56 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset2(t_dict *tmp, t_dict *before)
{
	t_dict	*point_to_free;

	free(tmp->key);
	free(tmp->value);
	if (before)
	{
		before->next = tmp->next;
		point_to_free = tmp;
	}
	else
	{
		point_to_free = tmp;
		g_env->envd = point_to_free->next;
	}
	free(point_to_free);
}

int		execute_unset(t_command *command)
{
	t_dict	*tmp;
	t_dict	*point_to_free;
	t_dict	*before;

	tmp = g_env->envd;
	before = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, command->argv[1]) == 0)
		{
			execute_unset2(tmp, before);
			break ;
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (0);
}
