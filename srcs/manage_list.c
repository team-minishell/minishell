/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:19:37 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/16 22:43:56 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_env_to_list(char **envp)
{
	int		i;
	t_list	*t;
	t_list	*start;

	i = 0;
	if (!(start = (t_list *)malloc(sizeof(t_list))))
		exit(MALLOC_ERROR);
	t = start;
	while (envp[i])
	{
		t->content = ft_strdup(envp[i]);
		if (!(t->next = (t_list *)malloc(sizeof(t_list))))
			exit(MALLOC_ERROR);
		t = t->next;
		i++;
	}
	return (start);
}

char	**make_list_to_envp(t_list *envl)
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
