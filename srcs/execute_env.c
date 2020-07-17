/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:42:34 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 20:14:50 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_env(char **tokens, t_env *env)
{
	t_dict *tmp;

	tmp = env->envd;
	while (tmp->key)
	{
		ft_printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return 0;
}