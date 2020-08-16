/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:05:12 by hna               #+#    #+#             */
/*   Updated: 2020/08/14 21:06:16 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** single quote(')와 double quote(")를 조건에 따라 열고 닫는다.
** 닫혀있음 : -1("hello world")
** 열려있음 : 1 ("hello world)
*/

void		check_quote(t_quote *q, char *line, int i)
{
	if (i == 0 && line[i] == '\"')
	{
		if (q->sq == -1)
			q->dq *= -1;
	}
	else if (i == 0 && line[i] == '\'')
	{
		if (q->dq == -1)
			q->sq *= -1;
	}
	else if (i != 0 && line[i] == '\"' && line[i - 1] != '\\')
	{
		if (q->sq == -1)
			q->dq *= -1;
	}
	else if (i != 0 && line[i] == '\'' && line[i - 1] != '\\')
	{
		if (q->dq == -1)
			q->sq *= -1;
	}
}

void		init_quote(t_quote *q)
{
	q->sq = -1;
	q->dq = -1;
}

int			is_quote_closed(t_quote *q)
{
	if (q->sq == -1 && q->dq == -1)
		return (1);
	return (0);
}
