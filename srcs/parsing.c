/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:37 by hna               #+#    #+#             */
/*   Updated: 2020/07/17 22:17:42 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 입력받은 문자열에서 환경변수 처리.
*/

char	*env_to_str(char *line, char **converted_line, t_dict *envd)
{
	int		i;
	int		len;
	char	*find;
	char	*target;
	t_dict	*convert_dict;

	find = ft_strnstr(line, " $", ft_strlen(line));
	if (find != 0)
	{
		i = (int)(find - line);
		i += 1;
		len = 0;
		while (ft_isalpha((int)line[++i]) || ft_isdigit((int)line[i]))
			len++;
		target = malloc(sizeof(char) * (len + 2));
		ft_strlcpy(target, &line[i - len - 1], len + 2);
		convert_dict = find_env(envd, &target[1]);
		if (convert_dict)
			*converted_line = convert_str(line, target, convert_dict->value);
		else
			*converted_line = convert_str(line, target, "");
		return (*converted_line);
	}
	return (0);
}

char	*parsing(char *line, t_dict *envd)
{
	t_dict	*home_dict;
	char	*converted_line;
	
	if (line[0] == '\0')
		return (NULL);
	home_dict = find_env(envd, "HOME");
	converted_line = convert_str(line, "~", home_dict->value);
	converted_line = env_to_str(line, &converted_line, envd);
	if (converted_line == 0)
		return (line);
	printf("line : %s\n", converted_line);
	return (converted_line);
}