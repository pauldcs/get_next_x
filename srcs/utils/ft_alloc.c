#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

bool	ft_alloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		write(STDERR_FILENO, "Out of memory\n", 14);
		return (false);
	}
	return (true);
}
