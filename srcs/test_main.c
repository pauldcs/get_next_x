#include "line_reader.h"
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

	if (ac == 2 && reader_init(&reader, open(av[1], O_RDONLY)))
	{
		while ((ret = line_reader(&line, '\n', &reader)) != -1)
		{
			write(STDOUT_FILENO, line, ret);
			write(STDOUT_FILENO, "\n", 1);
			free(line);
		}
		reader_destroy(&reader);
		close(reader.fd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
