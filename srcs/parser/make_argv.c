/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:45:43 by hna               #+#    #+#             */
/*   Updated: 2020/08/24 20:21:45 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strdup_alnum(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	ret = ft_strdup(str);
	ret[i] = '\0';
	return (ret);
}

char		*convert_str_free_str(char *str, char *s1, char *s2, int mode)
{
	char	*ret;

	ret = 0;
	if (mode == 0)
		ret = convert_str(str, s1, s2);
	else if (mode == 2)
	{
		ret = convert_str(str, s1, s2);
		free(s2);
	}
	else if (mode == 3)
	{
		ret = convert_str(str, s1, s2);
		free(s1);
		free(s2);
	}
	free(str);
	return (ret);
}

char		*convert_env(char *str)
{
	int		i;
	char	*target;
	char	*value;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			str = convert_str_free_str(str, "$?", ft_itoa(g_status), 2);
		else if (i == 0 && str[i] == '~' && \
				(str[i + 1] == 0 || str[i + 1] == '/'))
		{
			str = convert_str_free_str(str, "~", "$HOME", 0);
			i--;
		}
		else if (str[i] == '$' && str[i + 1] != '(')
		{
			target = ft_strdup_alnum(&str[i + 1]);
			value = find_value_in_dict(g_env->envd, target);
			str = convert_str_free_str(str, ft_strjoin("$", target), value, 3);
			free(target);
		}
	}
	return (str);
}

char		*delete_quote(char *str, int del_quote)
{
	int		len;

	if (del_quote != 0)
	{
		if (str[0] == '\'')
		{
			len = ft_strlen(str);
			ft_memmove(str, &str[1], len);
			str[len - 2] = '\0';
			return (str);
		}
		else if (str[0] == '\"')
		{
			len = ft_strlen(str);
			ft_memmove(str, &str[1], len);
			str[len - 2] = '\0';
		}
	}
	return (str);
}

/*
** create_job 에서 생성한 job->str을 이용해서
** 1. space를 기준으로 나누고 (split)
** 2. 앞뒤 공백을 제거 (ft_strtrim)
** 3. 따옴표에 따라 환경변수를 치환 (convert_env)
** 4. 따옴표 제거 (delete_quote)
** 5. command->cmd와 command->argv에 올바른 값을 넣는다.
*/

int			set_argv(t_job *job)
{
	int		i;
	int		n;
	int		del_quote;
	char	**splits;

	n = -1;
	while (++n < job->command->idx)
	{
		i = -1;
		splits = split_except_quote(((job->command) + n)->line, ' ');
		while (splits[++i])
		{
			splits[i] = ft_strtrim_free_s1(splits[i], " ");
			del_quote = (splits[i][0] == '\'' || splits[i][0] == '\"') ? 1 : 0;
			if (splits[i][0] != '\'')
			{
				splits[i] = escape_line(splits[i]);
				splits[i] = convert_env(splits[i]);
			}
			splits[i] = delete_quote(splits[i], del_quote);
		}
		((job->command) + n)->cmd = splits[0];
		((job->command) + n)->argv = splits;
	}
	return (0);
}
