#ifndef LINE_READER_H
# define LINE_READER_H

#include <stdbool.h>
#include <sys/types.h>
#include <stddef.h>

# define READ_SIZE 64

typedef struct s_reader
{
	int		fd;
	size_t	cap;
	size_t	checked;
	struct	s_save {
		const char	*buf;
		size_t		size;
	}	sv;
}	t_reader;

 
ssize_t	line_reader(uint8_t **buf, int chacarter, t_reader *reader);

bool	reader_init(t_reader *reader, int fd);
void	reader_destroy(t_reader *reader);

//utils
	bool	ft_alloc(void **ptr, size_t size);
	bool	ft_realloc(void **buf, size_t *cap, size_t len, size_t new_cap);

#endif
