/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:36:18 by hna               #+#    #+#             */
/*   Updated: 2020/08/18 20:25:23 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 현재 문자열부터 < 또는 > 기호가 나올때 까지의 문자열을 복제하고
** 공백문자를 제거한 문자를 리턴한다.
*/

char		*parse_path(char *str)
{
	int			i;
	char		*ret;
	t_quote		q;

	i = 0;
	init_quote(&q);
	ret = str;
	while (str[i])
	{
		check_quote(&q, str, i);
		if ((str[i] == '>' || str[i] == '<') && is_quote_closed(&q))
		{
			ret = ft_strdup(str);
			ret[i] = 0;
			break ;
		}
		i++;
	}
	if (ret)
		ret = ft_strtrim(ret, " ");
	return (ret);
}

/*
** 첫 리다이렉션이라면 새로 할당해준다.
** 아니라면 기존 리디렉션의 next에 할당한다.
*/

int			malloc_redirect(t_command *command, t_redi *redis)
{
	if (redis->new)
	{
		command->redirect = malloc(sizeof(t_redirect));
		(command->line)[redis->i] = 0;
		redis->first = command->redirect;
		redis->new = 0;
	}
	else
	{
		command->redirect->next = malloc(sizeof(t_redirect));
		command->redirect = command->redirect->next;
	}
	return (0);
}

/*
** redirect 기호를 확인하고 알맞은 값을 구조체에 넣어준다.
*/

int			make_redirect(t_command *cmd, t_redi *redis, char *str, t_quote *q)
{
	int		i;

	i = redis->i;
	if (str[i] == '>' && str[i + 1] == '>' && is_quote_closed(q))
	{
		malloc_redirect(cmd, redis);
		cmd->redirect->filepath = parse_path(&str[i + 2]);
		cmd->redirect->sign = DOUBLE_ARROW;
		cmd->redirect->next = 0;
		redis->i++;
	}
	else if ((str[i] == '>' || str[i] == '<') && is_quote_closed(q))
	{
		malloc_redirect(cmd, redis);
		cmd->redirect->filepath = parse_path(&str[i + 1]);
		cmd->redirect->sign = (str[i] == '>') ? RIGHT_ARROW : LEFT_ARROW;
		cmd->redirect->next = 0;
	}
	return (0);
}

/*
** jobs를 순회하면서 redirect 구조체를 할당하고 값을 넣어준다.
*/

void		init_redis(t_redi *redis)
{
	redis->i = 0;
	redis->first = 0;
	redis->new = 1;
}

int			make_redirects(t_job *job)
{
	t_redi		redis;
	int			n;
	t_quote		q;
	t_command	*command;
	char		*str;

	n = 0;
	while (n < job->command->idx)
	{
		command = (job->command) + n;
		init_redis(&redis);
		init_quote(&q);
		str = ft_strdup(command->line);
		while (str[redis.i])
		{
			check_quote(&q, str, redis.i);
			make_redirect(command, &redis, str, &q);
			redis.i++;
		}
		free(str);
		command->redirect = (redis.first);
		n++;
	}
	return (0);
}
