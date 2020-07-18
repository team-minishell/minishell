/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:19:37 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/19 05:30:46 by yochoi           ###   ########.fr       */
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
	while (envp[i] != NULL)
	{
		split = ft_split(envp[i], '=');
		t->key = ft_strdup(split[0]);
		t->value = ft_strdup(split[1]);
		/*if (!(t->next = (t_dict *)malloc(sizeof(t_dict))))
			exit(MALLOC_ERROR);
		t = t->next;*/
		i++;
		if (envp[i] != NULL)
		{
			if (!(t->next = (t_dict *)malloc(sizeof(t_dict))))
				exit(MALLOC_ERROR);
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
