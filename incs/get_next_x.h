#ifndef GET_NEXT_X_H
# define GET_NEXT_X_H

#include <stdbool.h>
#include <stddef.h>

# define READ_SIZE 64

typedef struct s_reader
{
	int		fd;
	bool	eof;
	size_t	cap;
	size_t	checked;
	struct	s_str {
		const char	*str;
		size_t		len;
	}	sv;
}	t_reader;

bool	get_next_x(char **line, int c, t_reader *r);
bool	reader_init(t_reader *r, int fd);
void	reader_destroy(t_reader *r);

//utils
	bool	ft_alloc(void **ptr, size_t size);
	bool	ft_realloc(char **buf, size_t *cap, size_t len, size_t new_cap);

#endif
