/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:10 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/12 21:21:05 by nahangyeol       ###   ########.fr       */
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

int		check_builtins(t_command *command) 
{
	
	if (!ft_strcmp(command->cmd, "cd"))
		execute_cd(command);
	else if (!ft_strcmp(command->cmd, "echo"))
		execute_echo(command);
	else if (!ft_strcmp(command->cmd, "env"))
		execute_env();
	else if (!ft_strcmp(command->cmd, "export"))
		execute_export(command);
	else if (!ft_strcmp(command->cmd, "pwd"))
		execute_pwd(command);
	else if (!ft_strcmp(command->cmd, "unset"))
		execute_unset(command);
	else
		return (1);
	return (0);
}

/*
** fork_pipe.c
*/

int		spawn_proc(int in, int out, t_command *command, t_job *job)
{
	int		i;
	char	**paths;
	char	*temp_path;
	char	*full_path;
	pid_t	pid;

	t_redirect	*redi;

	redi = command->redirect;
	if ((pid = fork()) == 0)
	{
		while (redi)
		{
			int		fd;
			if (redi->sign == RIGHT_ARROW)
			{
				redi->save_fd = dup(1);
				fd = open(redi->filepath, O_CREAT | O_WRONLY, 0777);
				if (fd < 0)
				{
					ft_printf("file open error\n");
					exit(0);
				}
				dup2(fd, 1);
				close(fd);
			}
			else if (redi->sign == LEFT_ARROW)
			{
				redi->save_fd = dup(0);
				fd = open(redi->filepath, O_RDONLY);
				if (fd < 0)
				{
					ft_printf("stdin : file open error\n");
					ft_printf("filepath:%s$\n", redi->filepath);
					exit(0);
				}
				dup2(fd, 0);
				close(fd);
			}
			else if (redi->sign == DOUBLE_ARROW)
			{
				redi->save_fd = dup(1);
				fd = open(redi->filepath, O_WRONLY | O_APPEND, 0777);
				if (fd < 0)
				{
					ft_printf("file open error\n");
					exit(0);
				}
				dup2(fd, 1);
				close(fd);
			}
			redi = redi->next;
		}
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
		paths = get_paths_from_envp(g_env->envp);
		i = 0;
		if (!check_builtins(command))
			;
		else
		{
			while (paths[i])
			{
				temp_path = ft_strjoin(paths[i], "/");
				full_path = ft_strjoin(temp_path, command->argv[0]);
				free(temp_path);
				execve(full_path, (char *const *)command->argv, g_env->envp); // 5. write(1, buffer, ...)방식의 출력 결과가, fd 1이 가리키는 곳으로 향한다. (파이프 입구 또는 표준 출력)
				i++;
			}
			if (errno)
				ft_perror(command->argv[0]);
		}
		exit(0);
	}	// 	결과가 파이프의 입력으로 들어감.
	return (pid);
}

/*
** redirect


int		set_redirect(t_redirect *redirect)
{
	int		fd;
	int		target_fd;

	while (redirect)
	{
		target_fd = (redirect->sign == LEFT_ARROW) ? 0 : 1;
		if (redirect->sign == RIGHT_ARROW)
			fd = open(redirect->filepath, O_CREAT | O_WRONLY, 0777);
		else if (redirect->sign == DOUBLE_ARROW)
			fd = open(redirect->filepath, O_APPEND);
		else if (redirect->sign == LEFT_ARROW)
			fd = open(redirect->filepath, O_RDONLY);
		else
		{
			ft_perror("redirection sign error\n");
			return (-1);
		}
		if (fd < 0 || errno)
		{
			ft_perror(strerror(errno));
			return (-1);
		}
		redirect->save_fd = dup(target_fd);
		dup2(fd, target_fd);
		redirect = redirect->next;
	}
	return (0);
}

int		reset_redirect(t_redirect *redirect)
{
	int		target_fd;

	target_fd = (redirect->sign == LEFT_ARROW) ? 0 : 1;
	if (target_fd < 0 || redirect == 0)
	{
		ft_perror("reset_redirect error\n");
		return (-1);
	}
	dup2(redirect->save_fd, target_fd);
	return (0);
}
*/

int		fork_pipes(int n, t_command *cmd, t_job *job)
{
	int		i;
	pid_t	pid;
	int		in, fd[2];

	in = 0; // 1. 맨처음엔 표준입력(0)을 입력으로 받는다.
	i = -1;
	// set_redirect()
	while (++i < n - 1)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd + i, job); // 2. 표준 입력(0)과 파이프 입구가 각각 in, out이 된다.(out 되는 값이 다시 파이프 입구에 들어가야하기 때문에) // 6. 파이프의 출구(fd[0])로 실행결과가 넘어온다.
		close(fd[1]); // 어차피 부모 프로세스에서는 파이프로 보낼게 없으므로, 부모 프로세서에서의 파이프 입구는 닫아둔다.
		in = fd[0]; // 7. 파이프의 출구를 다시 in과 연결한다.
	}
	// reset_redirect()
	pid = spawn_proc(in, 1, cmd + i, job);
	return (pid);
}

void	execute_job(t_job *job)
{
	pid_t	pid;
	int		status;

	while (job)
	{
		if ((job->str)[0] == '\0' || job->str == NULL)
			exit(MALLOC_ERROR);
		if (!ft_strcmp(job->command->cmd, "exit"))
			exit(0);
		pid = fork_pipes(job->command->idx, job->command, job);
		waitpid(pid, &status, 0);
		job = job->next;
	}
}
