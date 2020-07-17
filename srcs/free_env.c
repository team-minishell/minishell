/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 20:36:14 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 22:24:20 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_dict *tmp;

	if (env->envp)
		ft_split_del(env->envp);
	while (env->envd)
	{
		tmp = env->envd->next;
		free(env->envd->key);
		free(env->envd->value);
		free(env->envd);
		env->envd = tmp;
	}
	free(env);
}
