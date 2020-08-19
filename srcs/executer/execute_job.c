/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:53:10 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/18 16:04:30 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!ft_strcmp(command->cmd, "clear"))
		ft_printf("\ec");
	else if (!ft_strcmp(command->cmd, "exit"))
		;
	else
		return (1);
	return (0);
}

/*
** 1. command 배열의 갯수만큼 while을 돈다.
** 2. 커맨드에 길이 2이상의 배열이 생기는 경우는 파이프기호가 있다는 뜻이므로
**    while을 돌면서 파이프의 입구와 출구를 연결시켜면서
**    현재 command를 위한 프로세스를 만들고 실행시킨다.(spawn_proc();)
** 3. 길이가 1인 경우나 파이프의 마지막 명령은 출력(out)이 표준출력(1)으로 되도록 실행한다.
** *. 어차피 부모 프로세스에서는 파이프로 보낼게 없으므로, 부모 프로세서에서의 파이프 입구는 닫아둔다. (close(fd[1]);)
*/

int		fork_pipes(int n, t_command *command, t_job *job)
{
	int		i;
	pid_t	pid;
	int		in;
	int		fd[2];

	in = 0;
	i = -1;
	if ((!ft_strcmp(command->cmd, "export") ||
		(!ft_strcmp(command->cmd, "unset"))))
		check_builtins(command);
	else
	{
		while (++i < n - 1)
		{
			pipe(fd);
			spawn_proc(in, fd[1], command + i, job);
			close(fd[1]);
			in = fd[0];
		}
		pid = spawn_proc(in, 1, command + i, job);
	}
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
		if (!ft_strcmp(job->command->cmd, "cd"))
			execute_cd(job->command);
		else
		{
			pid = fork_pipes(job->command->idx, job->command, job);
			waitpid(pid, &status, 0);
		}
		job = job->next;
	}
}
