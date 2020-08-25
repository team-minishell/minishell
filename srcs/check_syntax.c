/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 20:57:24 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/26 00:09:32 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 파이프 기호나 리디렉션 기호로 split된 문자열의 첫 문자가 NULL 이라면,
** 문법 에러로 처리한다. (ex: >>>, |||, <<)
*/

int		is_valid_splits(char **splits)
{
	int		i;

	i = 0;
	while (splits[i])
	{
		if (splits[i][0] == 0)
		{
			write(2, "syntax error\n", 13);
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_pipe_syntax(char *str)
{
	int		i;
	char	**splits;

	splits = split_except_quote(str, '|');
	i = 0;
	while (splits[i])
	{
		splits[i] = ft_strtrim_free_s1(splits[i], " |\t\n");
		i++;
	}
	if (!is_valid_splits(splits))
		return (-1);
	ft_split_del(splits);
	return (0);
}

int		check_redirect_syntax_l(char *str)
{
	int		i;
	char	**splits;

	splits = split_except_quote(str, '<');
	i = 0;
	while (splits[i])
	{
		splits[i] = ft_strtrim_free_s1(splits[i], " <\t\n");
		i++;
	}
	if (!is_valid_splits(splits))
		return (-1);
	ft_split_del(splits);
	return (0);
}

int		check_redirect_syntax_r(char *str)
{
	int		i;
	int		end;
	char	**splits;

	splits = split_except_quote(str, '>');
	i = 0;
	while (splits[i])
	{
		splits[i] = ft_strtrim_free_s1(splits[i], " >\t\n");
		i++;
	}
	end = i - 1;
	i = 0;
	while (splits[i])
	{
		if (splits[0][0] == 0 || (end > 0 && splits[end][0] == 0) ||\
			((i > 0 && i < end) && splits[i][0] == 0 && splits[i + 1][0] == 0))
		{
			write(2, "syntax error\n", 13);
			return (-1);
		}
		i++;
	}
	ft_split_del(splits);
	return (0);
}

int		check_syntax(char *str)
{
	if (check_pipe_syntax(str) == -1)
		return (-1);
	if (check_redirect_syntax_l(str) == -1)
		return (-1);
	if (check_redirect_syntax_r(str) == -1)
		return (-1);
	return (0);
}
