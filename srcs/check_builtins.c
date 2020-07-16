/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:46:32 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/16 22:46:17 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtins(char **tokens, t_env *env)
{
	if (!ft_strcmp(tokens[0], "pwd"))
		execute_pwd(tokens);
	/*else if (!ft_strcmp(tokens[0], "echo"))
		echo(tokens); //미구현*/
	else if (!ft_strcmp(tokens[0], "cd"))
		execute_cd(tokens);
	/*else if (!ft_strcmp(tokens[0], "export"))
		export(tokens);
	else if (!ft_strcmp(tokens[0], "unset"))
		unset(tokens);*/
	else if (!ft_strcmp(tokens[0], "env"));
		//execute_env(tokens);
	else if (!ft_strcmp(tokens[0], "exit"))
		exit(0);
	else
		return (0);
	return (1);
}