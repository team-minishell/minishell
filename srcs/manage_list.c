/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:19:37 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 20:16:42 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*make_env_to_dict(char **envp)
{
	int		i;
	char	**split;
	t_dict	*t;
	t_dict	*start;

	i = 0;
	if (!(start = (t_dict *)malloc(sizeof(t_dict))))
		exit(MALLOC_ERROR);
	t = start;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		t->key = ft_strdup(split[0]);
		t->value = ft_strdup(split[1]);
		if (!(t->next = (t_dict *)malloc(sizeof(t_dict))))
			exit(MALLOC_ERROR);
		t = t->next;
		i++;
		ft_split_del(split);
	}
	return (start);
}

char	**make_dict_to_envp(t_dict *envd)
{
	char	**envp;
	int		i;
	int		lst_len;
	int		str_len;

	i = 0;
	lst_len = ft_lstsize(envd);
	if (!(envp = (char **)malloc(sizeof(char *) * (lst_len + 1))))
		exit(MALLOC_ERROR);
	while (i < lst_len)
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
	return (envp);
}

char	**make_list_to_envp(t_dict *envl)
{
	char	**envp;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(envl);
	if (!(envp = (char **)malloc(sizeof(char *) * (len + 1))))
		exit(MALLOC_ERROR);
	while (envl->content != 0)
	{
		envp[i] = ft_strdup((char *)envl->content);
		envl = envl->next;
		i++;
	}
	envp[len] = 0;
	// envp 2차원 배열 확인용 테스트 코드
	// printf("======test=====\n");
	// i = 0;
	// while (envp[i])
	// {
	// 	printf("%d: %s\n", i, envp[i]);
	// 	i++;
	// }
	return (envp);
}

/*
char	*find_env(t_dict *envl, char *key)
{
	char	**key_value;
	char	*value;

	while (envl->content)
	{
		key_value = ft_split(envl->content, '=');
		if (ft_strcmp(key_value[0], key) == 0)
			value = key_value[1];
	}
}
*/