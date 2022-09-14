/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:17:28 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 21:12:18 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool	__alloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		write(STDERR_FILENO, "Out of memory\n", 14);
		return (false);
	}
	return (true);
}

bool    ft_realloc(void **buf, size_t *cap, size_t len, size_t new_cap)
{
   void    *new_buf;

    if (!__alloc(&new_buf, new_cap))
        return (false);
    memcpy(new_buf, *buf, len);
    free(*buf);
    *buf = new_buf;
    *cap = new_cap;
    return (true);
}
