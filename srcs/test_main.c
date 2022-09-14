#include "get_next_x.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	char		*line;
	t_reader 	reader;

	if (ac == 2
		&& reader_init(&reader, open(av[1], O_RDONLY)))
	{
		while (get_next_x(&line, '\n', &reader))
		{
			printf("%s\n", line);
			free(line);
		}
		reader_destroy(&reader);
		return (0);
	}
	return 1;
}
