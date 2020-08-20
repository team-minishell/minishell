/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:45:43 by hna               #+#    #+#             */
/*   Updated: 2020/08/20 21:19:47 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*convert_env(char *str)
{
	int		i;
	char	*target;
	char	*value;
	char	*key;
	char	*ret;

	i = 0;
	ret = str;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			target = ft_strdup(&str[i]);
			ret = convert_str(str, "$?", ft_itoa(g_status));
			free(target);
			free(str);
			str = ret;
		}
		else if (str[i] == '$' && str[i + 1] != '(')
		{
			value = find_value_in_dict(g_env->envd, &str[i + 1]);
			target = ft_strdup(&str[i]);
			ret = convert_str(str, target, value);
			free(value);
			free(target);
			free(str);
			str = ret;
		}
		i++;
	}
	return (ret);
}

char		*delete_quote_convert_env(char *str)
{
	int		len;
	char	*temp;
	char	*key;

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
	str = convert_env(str);
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
	char	**splits;

	n = 0;
	while (n < job->command->idx)
	{
		i = 0;
		splits = split_except_quote(((job->command) + n)->line, ' ');
		while (splits[i])
		{
			splits[i] = ft_strtrim_free_s1(splits[i], " ");
			splits[i] = delete_quote_convert_env(splits[i]);
			i++;
		}
		((job->command) + n)->cmd = splits[0];
		((job->command) + n)->argv = splits;
		n++;
	}
	return (0);
}
