#include "get_next_x.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	unsigned char	*line;
	ssize_t			ret;
	t_reader 		reader;

	if (ac == 2
		&& reader_init(&reader, open(av[1], O_RDONLY)))
	{
		while ((ret = get_next_x(&line, '\n', &reader)) != -1)
		{
			write (1, line, ret);
			write (1, "\n", 1);
			//printf("%s\n", line);
			free(line);
		}
		reader_destroy(&reader);
		return (0);
	}
	return 1;
}
