/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:25:36 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/12 21:12:44 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_export(t_command *command)
{
	char	**splits;
	t_dict	*envd;
	t_dict	*new;

	envd = g_env->envd;
	splits = ft_split(command->argv[1], '=');
	if (!(new = malloc(sizeof(t_dict) * 1)))
		exit(MALLOC_ERROR);
	g_env->envd = new;
	new->next = envd;
	new->key = splits[0];
	new->value = splits[1];
	ft_split_del(splits);
	return (0);
}
