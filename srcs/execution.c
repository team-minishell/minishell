/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:10 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/06 23:39:59 by nahangyeol       ###   ########.fr       */
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

int		check_builtins(t_job *job)
{
	char *cmd;

	cmd = job->command->cmd;
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

/////
int		spawn_proc(int in, int out, t_command *cmd)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0) // 3. in으로 설정한 값이 파이프 출구라면, 파이프 출구를 표준 입력으로 받는다.
		{
			dup2(in, 0);	// in = 파이프 출구 = 표준입력 // write(0, ...)
			close(in);		// fd 절약, 어차피 fd 0번만 쓰기때문에 기존 fd는 닫아도 된다.
		}
		if (out != 1) // 4. out으로 설정한 값이 파이프 입구라면, 파이프 입구와 표준출력을 연결한다.
		{
			dup2(out, 1);	// out = 파이프 입구 = 표준출력 // write(1, ...)
			close(out);
		}
		return execvp(cmd->argv[0], (char *const *)cmd->argv);	// 5. write(1, buffer, ...)방식의 출력 결과가, fd 1이 가리키는 곳으로 향한다. (파이프 입구 또는 표준 출력)
	}	// 	결과가 파이프의 입력으로 들어감.
	return (pid);
}
int		fork_pipes(int n, t_command *cmd)
{
	int		i;
	pid_t	pid;
	int		in, fd[2];

	in = 0; // 1. 맨처음엔 표준입력(0)을 입력으로 받는다.
	i = -1;
	while (++i < n - 1)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd + i); // 2. 표준 입력(0)과 파이프 입구가 각각 in, out이 된다.(out 되는 값이 다시 파이프 입구에 들어가야하기 때문에) // 6. 파이프의 출구(fd[0])로 실행결과가 넘어온다.
		close(fd[1]); // 어차피 부모 프로세스에서는 파이프로 보낼게 없으므로, 부모 프로세서에서의 파이프 입구는 닫아둔다.
		in = fd[0]; // 7. 파이프의 출구를 다시 in과 연결한다.
	}
	pid = spawn_proc(in, 1, cmd + i);
	return (pid);
}
////

void	execute_job(t_job *job)
{
	pid_t	pid;
	char	**tokens;
	int		status;

	while (job)
	{
		if ((job->str)[0] == '\0' || job->str == NULL)
			exit(MALLOC_ERROR);
		tokens = job->command->argv;
		if (!check_redirect(job) || !check_builtins(job))
			;
		else
		{
			// pid = fork();
			// if (pid == 0)
			// {
			// 	execute_with_envp(tokens, g_env->envp);
			// 	exit(0);
			// }
			pid = fork_pipes(1, job->command);
			waitpid(pid, &status, 0);
		}
		job = job->next;
	}
}
