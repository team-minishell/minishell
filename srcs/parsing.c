/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:37 by hna               #+#    #+#             */
/*   Updated: 2020/07/17 19:57:49 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 
*/

char	*parsing(char *line, t_list *envl)
{
	// int		len;
	// char	*home_dir;
	char	*converted_line;

	/*
	while (envl->content)
	{
		if (ft_strcmp(envl->content, "HOME") == 0)
			home_dir = envl->content;
		envl = envl->next;
	}
	*/
	//home_dir = find_env(envl, "HOME");
	converted_line = convert_str(line, "~", "/Users/yochoi");
	if (converted_line == 0)
		return (line);
	return (converted_line);
}