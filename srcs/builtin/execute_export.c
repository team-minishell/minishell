/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:25:36 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/25 23:56:16 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_export(char **tokens)
{
	char	**splits;
	t_dict	*envd;
	t_dict	*new;

	envd = g_env->envd;
	splits = ft_split(tokens[1], '=');
	if (!(new = malloc(sizeof(t_dict) * 1)))
		exit(MALLOC_ERROR);
	g_env->envd = new;
	new->next = envd;
	new->key = splits[0];
	new->value = splits[1];
	free(splits);
	return (1);
}
