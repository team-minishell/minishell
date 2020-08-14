/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:36:18 by hna               #+#    #+#             */
/*   Updated: 2020/08/14 21:16:32 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			malloc_redirect(t_command *command, t_redirect **f, int i, int *new)
{
	if (*new)
	{
		command->redirect = malloc(sizeof(t_redirect));
		(command->line)[i] = 0;
		*f = command->redirect;
		*new = 0;
	}
	else
	{
		command->redirect->next = malloc(sizeof(t_redirect));
		command->redirect = command->redirect->next;
	}
	return (0);
}

int			make_redirects(t_job *job)
{
	int			i;
	int			n;
	t_quote		q;
	t_command	*command;
	t_redirect	*redirect;
	t_redirect	*first;
	char		*str;
	int			new;

	n = 0;
	while (n < job->command->idx)
	{
		first = 0;
		i = 0;
		command = (job->command) + n;
		new = 1;
		str = ft_strdup(command->line);
		init_quote(&q);
		while (str[i])
		{
			check_quote(&q, str, i);
			if (str[i] == '>' && str[i + 1] == '>' && is_quote_closed(&q))
			{
				malloc_redirect(command, &first, i, &new);
				command->redirect->filepath = parse_path(&str[i + 2]);
				command->redirect->sign = DOUBLE_ARROW;
				command->redirect->next = 0;
				i++;
			}
			else if ((str[i] == '>' || str[i] == '<') && is_quote_closed(&q))
			{
				malloc_redirect(command, &first, i, &new);
				command->redirect->filepath = parse_path(&str[i + 1]);
				command->redirect->sign = (str[i] == '>') ? RIGHT_ARROW : LEFT_ARROW;
				command->redirect->next = 0;
			}
			i++;
		}
		free(str);
		command->redirect = first;
		n++;
	}
	return (0);
}
