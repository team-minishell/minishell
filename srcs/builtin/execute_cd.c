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

int		execute_cd(char **tokens)
{
	int		len;
	t_dict	*home;

	home = find_env(g_env->envd, "HOME");
	len = ft_split_len(tokens);
	if (len == 1)
	{
		chdir(home->value);
		return (0);
	}
	chdir(tokens[1]);
	return (0);
}