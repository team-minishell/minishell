/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:25:36 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/19 04:48:25 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** use ft_split_del
*/

/*void	free_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}*/

int		execute_export(char **tokens, t_env *env)
{
	char	**splits;
	t_dict	*envd;
	t_dict	*new;

	envd = env->envd;
	// if (!(is_valid_token(tokens[1])))
	// 	ft_printf("")
	splits = ft_split(tokens[1], '=');
	if (!(new = malloc(sizeof(t_dict) * 1)))
		exit(MALLOC_ERROR);
	env->envd = new;
	new->next = envd;
	new->key = splits[0];
	new->value = splits[1];
	free(splits);
	return (1);
}
