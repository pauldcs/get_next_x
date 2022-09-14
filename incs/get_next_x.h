#ifndef GET_NEXT_X_H
# define GET_NEXT_X_H

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

 
ssize_t	get_next_x(unsigned char **buf, int chacarter, t_reader *reader);

bool	reader_init(t_reader *reader, int fd);
void	reader_destroy(t_reader *reader);

//utils
	bool	ft_alloc(void **ptr, size_t size);
	bool	ft_realloc(void **buf, size_t *cap, size_t len, size_t new_cap);

#endif
