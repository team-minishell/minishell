/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:23:34 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/26 00:03:10 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 2차원 배열 환경변수를 딕셔너리로 변환한다.
*/

t_dict	*make_env_to_dict(char **envp)
{
	int		i;
	char	**split;
	t_dict	*t;
	t_dict	*start;

	i = 0;
	start = (t_dict *)malloc(sizeof(t_dict));
	t = start;
	while (envp[i] != NULL)
	{
		split = ft_split(envp[i], '=');
		t->key = ft_strdup(split[0]);
		if (split[1] != NULL)
			t->value = ft_strdup(split[1]);
		else
			t->value = ft_strdup("");
		if (envp[++i] != NULL)
		{
			t->next = (t_dict *)malloc(sizeof(t_dict));
			t = t->next;
		}
		ft_split_del(split);
	}
	t->next = NULL;
	return (start);
}

int		dict_size(t_dict *dict)
{
	int		i;

	i = 0;
	while (dict)
	{
		dict = dict->next;
		i++;
	}
	return (i);
}

/*
** 환경변수 딕셔너리를 2차원 배열로 변환한다.
*/

char	**make_dict_to_envp(t_dict *envd)
{
	char	**envp;
	int		i;
	int		lst_len;
	int		str_len;

	i = 0;
	lst_len = dict_size(envd);
	if (!(envp = (char **)malloc(sizeof(char *) * (lst_len + 1))))
		exit(MALLOC_ERROR);
	while (i < lst_len - 2)
	{
		str_len = ft_strlen(envd->key) + ft_strlen(envd->value) + 2;
		if (!(envp[i] = malloc(sizeof(char) * str_len)))
			exit(MALLOC_ERROR);
		envp[i][0] = '\0';
		ft_strlcat(envp[i], envd->key, str_len);
		ft_strlcat(envp[i], "=", str_len);
		ft_strlcat(envp[i], envd->value, str_len);
		envd = envd->next;
		i++;
	}
	envp[i] = 0;
	return (envp);
}

/*
** 키 문자열로 딕셔너리에서 값을 찾아 반환한다.
*/

t_dict	*find_env(t_dict *envd, char *key)
{
	while (envd)
	{
		if (ft_strcmp(envd->key, key) == 0)
			return (envd);
		envd = envd->next;
	}
	return (0);
}

char	*find_value_in_dict(t_dict *envd, char *key)
{
	char	*str;

	while (envd)
	{
		if (ft_strcmp(envd->key, key) == 0)
		{
			str = ft_strdup(envd->value);
			return (str);
		}
		envd = envd->next;
	}
	return (ft_strdup(""));
}
