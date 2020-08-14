/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:30:17 by hna               #+#    #+#             */
/*   Updated: 2020/08/14 20:35:15 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** strtrim과 같은데 입력받은 s1을 free해준다.
*/

char		*ft_strtrim_free_s1(char *s1, char *set)
{
	char	*new_str;

	new_str = ft_strtrim(s1, set);
	free(s1);
	return (new_str);
}

/*
** command[i]->line 에 redirect나 argv로 나눠지기 전 문자열을 입력한다.
** "echo a > a.txt"
*/

int			set_command_line(t_job *job, char **cmds)
{
	int		n;

	n = 0;
	while (n < job->command->idx)
	{
		((job->command) + n)->line = cmds[n];
		((job->command) + n)->redirect = 0;
		n++;
	}
	return (0);
}

/*
** 파이프 기호 갯수만큼 command 구조체 배열을 할당한다.
** 이후 파이프로 나눠진 명령을 입력한다.
*/

int			make_commands(t_job *job)
{
	int		n;
	char	**cmds;

	cmds = split_except_quote(job->str, '|');
	n = 0;
	while (cmds[n])
	{
		cmds[n] = ft_strtrim_free_s1(cmds[n], " |");
		n++;
	}
	job->command = malloc(sizeof(t_command) * n);
	job->command->idx = n;
	set_command_line(job, cmds);
	free(cmds);
	return (0);
}
