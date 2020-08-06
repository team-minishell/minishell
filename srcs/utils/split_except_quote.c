#include "minishell.h"

/*
** splits_except_quote.c
** 기존 ft_split과 같은데, 따옴표 안에 있는 문자는 무시한다.
*/

typedef struct	s_split
{
	int		i;
	int		start;
	int		len;
	int		split_idx;
}				t_split;

/*
** split 구조체 초기화
*/

void		init_split(t_split *spt)
{
	spt->i = 0;
	spt->len = 0;
	spt->start = 0;
	spt->split_idx = 0;
}

int			get_split_len(char *str, char c)
{
	int		i;
	int		ret;
	t_quote	q;

	i = 0;
	ret = 0;
	q.dq = -1;
	q.sq = -1;
	while (str[i])
	{
		check_quote(&q, str, i);
		if (str[i] == c && (q.sq == -1 && q.dq == -1))
			ret++;
		i++;
	}
	return (ret);
}

char		**malloc_splits(char *str, char c)
{
	char	**splits;
	int		split_len;

	split_len = get_split_len(str, c);
	if (!(splits = (char **)malloc(sizeof(char *) * (split_len + 2))))
		exit(MALLOC_ERROR);
	splits[split_len + 1] = NULL;
	return (splits);
}

char		**split_except_quote(char *str, char c)
{
	char	**splits;
	t_quote	q;
	t_split	sp;

	init_split(&sp);
	splits = malloc_splits(str, c);
	q.dq = -1;
	q.sq = -1;
	while (str[sp.i])
	{
		sp.len++;
		check_quote(&q, str, sp.i);
		if ((str[sp.i] == c && (q.sq == -1 && q.dq == -1)) \
		|| str[sp.i + 1] == '\0')
		{
			splits[sp.split_idx] = ft_strdup(&str[sp.start]);
			ft_strlcpy(splits[sp.split_idx], &str[sp.start], sp.len + 1);
			sp.split_idx++;
			sp.len = 0;
			sp.start = sp.i + 1;
		}
		sp.i++;
	}
	splits[sp.split_idx] = NULL;
	return (splits);
}