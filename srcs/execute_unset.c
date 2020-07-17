/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 21:26:06 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 22:27:25 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_unset(char **tokens, t_env *env)
{
	int		i;
	t_dict	*next;
	t_dict	*before;
	t_dict	*tmp;

	i = 0;
	tmp = env->envd;
	while (i < dict_size(env->envd) - 1)
	{
		next = tmp->next;
		if (ft_strcmp(tmp->key, tokens[1]) == 0)
		{
			free(tmp->key);
			free(tmp->value);
			if (i == 0)
			{
				env->envd = tmp->next;
				free(tmp);
			}
			else
			{
				next = tmp->next;
				free(tmp);
				before->next = next;
				free(env->envp);
				env->envp = make_dict_to_envp(env->envd);
			}
		}
		before = tmp;
		tmp = tmp->next;
		i++;
	}
	return (1);
}
