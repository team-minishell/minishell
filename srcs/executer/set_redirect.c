/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:18:23 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/18 15:20:48 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 1. 실행 할 프로세스의 입력이 표준입력이 아니라면, 표준입력(0번)이 파이프의 입구(in번)가 되도록 한다.
** 2. 출력도 표준출력으로 해줄게 아니라면, 표준출력 fd가 out의 참조값을 가리키도록 한다.
*/

int		set_in_and_out(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

/*
** redirect에 따라서 출력값이나 입력값이 파일에 쓰여지도록 fd를 새로 설정한다.
*/

int		set_dup(t_redirect *redirect, int fd1, int fd2)
{
	redirect->save_fd = dup(fd2);
	dup2(fd1, fd2);
	close(fd1);
	return (0);
}

int		set_redirect(t_redirect *redirect)
{
	int		fd;

	while (redirect)
	{
		if (redirect->sign == RIGHT_ARROW || redirect->sign == DOUBLE_ARROW)
		{
			if (redirect->sign == RIGHT_ARROW)
				fd = open(redirect->filepath, O_CREAT | O_WRONLY, 0777);
			else
				fd = open(redirect->filepath, O_WRONLY | O_APPEND, 0777);
			if (errno && ft_perror("", errno))
				continue ;
			set_dup(redirect, fd, 1);
		}
		else if (redirect->sign == LEFT_ARROW)
		{
			fd = open(redirect->filepath, O_RDONLY);
			if (errno && ft_perror("", errno))
				continue ;
			set_dup(redirect, fd, 0);
		}
		redirect = redirect->next;
	}
	return (0);
}
