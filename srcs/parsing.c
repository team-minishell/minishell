/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:37 by hna               #+#    #+#             */
/*   Updated: 2020/07/17 21:16:59 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 
*/

int		is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*parsing(char *line, t_dict *envd)
{
	char	*home_dir;
	char	*converted_line;
	
	if (line[0] == '\0')
		return (NULL);
	home_dir = find_env(envd, "HOME");
	converted_line = convert_str(line, "~", home_dir);

	int		i;
	int		len;
	char	*find;
	char	*target;
	char	*convert;

	find = ft_strnstr(line, " $", ft_strlen(line));
	if (find != 0)
	{
		i = (int)(find - line);
		i += 2;
		len = 0;
		while (is_alpha(line[i]) || is_digit(line[i]))
		{
			i++;
			len++;
		}
		target = malloc(sizeof(char) * (len + 2));
		ft_strlcpy(target, &line[i - len - 1], len + 2);
		// printf("%s\n", target);
		convert = find_env(envd, &target[1]);
		if (convert)
			converted_line = convert_str(line, target, convert);
		else
			converted_line = convert_str(line, target, "");
	}
	if (converted_line == 0)
		return (line);
	printf("line : %s\n", converted_line);
	return (converted_line);
}