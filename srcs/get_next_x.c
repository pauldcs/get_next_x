/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:17:02 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 20:43:06 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// implement support for bin files
// add support for any char, not just new_lines

/*
static char	*str_ndup(const char *str, size_t n)
{
	char	*new;

	if (!ft_alloc((void **)&new, n + 1))
		return (NULL);
	new[n] = '\0';
	while (n--)
		new[n] = str[n];
	return (new);
}
*/

static bool	init_buf(t_reader *r, char **buf, size_t *size)
{	
	if (r->sv.str)
	{
		*buf = (char *)r->sv.str;
		*size = r->sv.len;
		r->cap = *size;
	}
	else
	{
		if (!ft_alloc((void **)buf, READ_SIZE + 1))
			return (false);
		r->cap = READ_SIZE;
		*size = 0;
	}
	r->sv.str = NULL;
	r->sv.len = 0;
	r->checked = 0;
	return (true);
}

static bool	search_char(t_reader *r, int c, char *buf, size_t len)
{
	char	*ptr;
	size_t	n;

	ptr = buf + r->checked;
	n = len - r->checked;
	while (n--)
	{
		if (*ptr != c && ptr++)
			continue ;
		*ptr = '\0';
		len -= ptr - buf + 1;
		if (len && *++ptr)
		{
			if (!ft_alloc((void **)&r->sv.str, len))
				return (false);
			memcpy((char *)r->sv.str, ptr, len);
			r->sv.len = len;
		}
		return (true);
	}
	r->checked = ptr - buf;
	return (false);
}

ssize_t	get_next_x(char **buf, int c, t_reader *r)
{
	size_t	size;
	int		ret;

	if (r->eof
		|| !init_buf(r, buf, &size))
		return (-1);
	while (!search_char(r, c, *buf, size))
	{
		if (size >= r->cap - 1
			&& !ft_realloc(buf, &r->cap, size, r->cap * 2 + 1))
			return (free(*buf), -1);
		ret = read(r->fd, &(*buf)[size], r->cap - size - 1);
		if (ret == -1
			|| (!ret && !size))
			return (free(*buf), -1);
		else if (!ret)
		{
			return (size);
			r->eof = true;
		}
		size += ret;
	}
	return (size - r->sv.len - 1);
}
