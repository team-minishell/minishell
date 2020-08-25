/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:11:02 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/26 00:19:10 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 1. 환경변수(envp)중 PATH 환경변수를 찾는다.
** 2. 찾았다면, PATH의 문자열을 :으로 split한다.
** 3. split된 결과(paths)를 return한다.
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

void	print_my_error(char *cmd, int my_err_num)
{
	ft_putstr_fd(cmd, 2);
	if (my_err_num == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (my_err_num == 2)
		ft_putstr_fd(": no usch file or directory\n", 2);
}

int		execve_with_path(char *path, char *cmd, char **argv, char **envp)
{
	int		ret;
	char	*full_path;
	char	*temp_path;

	ret = 0;
	temp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	ret = execve(full_path, argv, envp);
	free(full_path);
	return (ret);
}

/*
** 1. get_paths_from_envp로 경로들을 가져온다.
** 2. PATH 경로 없이 실행시켜본다.
** 3. paths들에 있는 기본경로들을 join 해보면서 실행시킨다.
** 4. 메모리 해제 및 에러처리
*/

int		execve_with_envp(char *cmd, char **argv, char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	if ((cmd[i] == '.' || cmd[i] == '/') && (execve(cmd, argv, envp) == -1))
		ft_perror(cmd, errno);
	else
	{
		paths = get_paths_from_envp(envp);
		if (paths != 0)
		{
			while (paths[i])
			{
				execve_with_path(paths[i], cmd, argv, envp);
				i++;
			}
			print_my_error(cmd, 1);
			ft_split_del(paths);
			return (-1);
		}
		print_my_error(cmd, 2);
	}
	return (0);
}

/*
** 자식 프로세스를 만들고 그안에서 커맨드를 실행시킨다.
** 1. fork
** 2. redirect 설정
** 3. 커맨드 실행
*/

int		spawn_proc(int in, int out, t_command *command, t_job *job)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		set_in_and_out(in, out);
		set_redirect(command->redirect);
		if (!check_builtins(command))
			;
		else
			execve_with_envp(command->cmd, command->argv, g_env->envp);
		exit(12);
	}
	return (pid);
}
