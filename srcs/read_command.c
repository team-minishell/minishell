/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:10 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/16 20:34:50 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** PATH를 콜론으로 구분함
*/

char	**get_paths_from_envp(char **envp)
{
	int		i;
	char	**splits;
	char	**paths;
	char	*path_str;

	i = 0;
	while (envp[i])
	{
		splits = ft_split(envp[i], '=');
		if (ft_strcmp("PATH", splits[0]) == 0)
		{
			paths = ft_split(splits[1], ':');
			ft_split_del(splits);
			return (paths);
		}
		i++;
	}
	return (0);
}

/*
** PATH를 하나하나 확인해봄
*/
void	execute_with_envp(char **tokens, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;
	i = 0;
	paths = get_paths_from_envp(envp);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, tokens[0]);
		execve(full_path, tokens, envp);
		i++;
	}
	ft_split_del(paths);
	if (errno)
		ft_perror(tokens[0]);
}

int		execution(char *str, char **envp)
{
	pid_t	pid;
	char	**tokens;
	int		status;
	tokens = ft_split(str, ' ');
	pid = fork();
	if (pid == 0)
	{
		execute_with_envp(tokens, envp);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (1);
}