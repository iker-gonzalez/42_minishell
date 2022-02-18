#include <unistd.h>
#include <string.h>

int	echo(int argc, char **argv, int fd)
{
	int	i;
	size_t	cnt;
	
	if (!fd)
		fd = 1;
	i = 1;
	if (strcmp(argv[i], "-n") == 0)
		i++;
	while (i < argc)
	{
		cnt = strlen(argv[i]);
		write(fd, argv[i], cnt);
		if (i != argc - 1)
			write(fd, " ", 1);
		i++;
	}
	if (fd == 1 && (strcmp(argv[1], "-n") != 0))
		write(fd, "\n", 1);
	return (0);
}
