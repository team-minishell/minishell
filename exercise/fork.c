#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	int	x;
	int	pid;

	x = 0;
	pid = fork();
	if (pid > 0)
	{
		x = 1;
		printf("부모%d\n", x);
	}
	else if (pid == 0)
	{
		x = 2;
		printf("자식%d\n", x);
	}
	else
		printf("포크 실패\n");
	return (0);
}