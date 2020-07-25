#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (start > strlen(s))
		return (strdup(""));
	if (!(str = calloc(len + 1, sizeof(char))))
		return (0);
	i = 0;
	while (i < len && s[i + start] != 0)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (0);
	while (*(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j) != '\0')
	{
		*(str + i) = *(s2 + j);
		i++;
		j++;
	}
	*(str + i) = '\0';
	return (str);
}

static char	*stack_buff_join(char *stack, char *buff)
{
	char	*temp;

	temp = ft_strjoin(stack, buff);
	free(stack);
	free(buff);
	return (temp);
}

static char	*update_line(char *stack, int ret)
{
	char	*line;
	int		i;

	line = 0;
	i = 0;
	if (ret == 0)
		line = strdup(stack);
	else if (ret > 0)
	{
		while (stack[i] != '\n')
			i++;
		line = substr(stack, 0, i);
	}
	return (line);
}

static char	*update_stack(char *stack, int ret)
{
	int		i;
	char	*temp;

	temp = 0;
	i = 0;
	if (ret > 0)
	{
		while (stack[i] != '\n')
			i++;
		temp = ft_strdup(stack + i + 1);
	}
	free(stack);
	stack = NULL;
	return (temp);
}

int			get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	int			ret;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	ret = 1;
	if (stack[fd] == 0)
		stack[fd] = ft_strdup("");
	while (ft_strchr(stack[fd], '\n') == 0 && ret > 0)
	{
		if (!(buff = ft_calloc(1, BUFFER_SIZE + 1)) ||
				(ret = read(fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		stack[fd] = stack_buff_join(stack[fd], buff);
	}
	*line = update_line(stack[fd], ret);
	stack[fd] = update_stack(stack[fd], ret);
	return (ret > 0 ? 1 : ret);
}