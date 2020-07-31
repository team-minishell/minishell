/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:10 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/25 22:04:34 by nahangyeol       ###   ########.fr       */
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
		execve(tokens[0], tokens, envp);
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, tokens[0]);
		execve(full_path, tokens, envp);
		i++;
	}
	ft_split_del(paths);
	if (errno)
		ft_perror(tokens[0]);
}

/*
** 명령어와 인자를 공백으로 구분하고
** 빌트인 명령어면 빌트인 명령어를 실행하고
** 빌트인 명령어가 아니면 execute_with_envp 함수로 PATH에 있는
** 명령어를 실행함
*/

/*int		execution(char *str, t_env *env)
{
	pid_t	pid;
	char	**tokens;
	int		status;

	// check_pipe
	tokens = ft_split(str, ' ');
	if (!check_builtins(tokens, env))
		;
	else
	{
		pid = fork();
		if (pid == 0)								이제 안쓸 함순가요?
		{
			execute_with_envp(tokens, env->envp);
			exit(0);
		}
		waitpid(pid, &status, 0);
	}
	ft_split_del(tokens);
	return (1);
}*/

int		check_builtins(t_job *job)
{
	char *cmd;

	cmd = job->command.cmd;
	if (!ft_strcmp(cmd, "cd"))
		execute_cd(job);
	else if (!ft_strcmp(cmd, "echo"))
		execute_echo(job);
	else if (!ft_strcmp(cmd, "env"))
		execute_env();
	else if (!ft_strcmp(cmd, "export"))
		execute_export(job);
	else if (!ft_strcmp(cmd, "pwd"))
		execute_pwd(job);
	else if (!ft_strcmp(cmd, "unset"))
		execute_unset(job);
	else if (!ft_strcmp(cmd, "exit"))
		exit(0);
	else
		return (1);
	return (0);
}

void	execute_job(t_job *job)
{
	pid_t	pid;
	char	**tokens;
	int		status;

	while (job)
	{
		if ((job->str)[0] == '\0' || job->str == NULL)
			exit(MALLOC_ERROR);
		tokens = job->command.argv; //job->command.argv에는 인자만 들어가야 하는거 아닌가요?
		if (!check_builtins(job))
			;
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execute_with_envp(tokens, g_env->envp);
				exit(0);
			}
			waitpid(pid, &status, 0);
		}
		job = job->next;
	}
}
