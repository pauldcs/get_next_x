/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:17:02 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 23:07:03 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool	init_buf(t_reader *r, unsigned char **buf, size_t *size)
{	
	if (r->sv.buf)
	{
		*buf = (unsigned char *)r->sv.buf;
		*size = r->sv.size;
		r->cap = *size;
	}
	else
	{
		if (!ft_alloc((void **)buf, READ_SIZE + 1))
			return (false);
		r->cap = READ_SIZE;
		*size = 0;
	}
	r->sv.buf = NULL;
	r->sv.size = 0;
	r->checked = 0;
	return (true);
}

static bool	search_char(t_reader *r, int c, unsigned char *buf, size_t len)
{
	unsigned char	*ptr;
	size_t			n;

	ptr = buf + r->checked;
	n = len - r->checked;
	while (n--)
	{
		if (*ptr != c && ptr++)
			continue ;
		*ptr++ = '\0';
		len -= ptr - buf;
		if (len)
		{
			if (!ft_alloc((void **)&r->sv.buf, len)
				|| !memcpy((void *)r->sv.buf, ptr, len))
				return (false);
			r->sv.size = len;
		}
		return (true);
	}
	r->checked = ptr - buf;
	return (false);
}

ssize_t	get_next_x(unsigned char **buf, int c, t_reader *r)
{
	size_t	size;
	int		ret;

	if (r->eof || !init_buf(r, buf, &size))
		return (-1);
	while (!search_char(r, c, *buf, size))
	{
		if (size >= r->cap - 1
			&& !ft_realloc((void **)buf, &r->cap, size, r->cap * 2 + 1))
			return (-1);
		ret = read(r->fd, &(*buf)[size], r->cap - size - 1);
		if (ret == -1
			|| (!ret && !size))
			return (free(*buf), -1);
		else if (!ret)
		{
			r->eof = true;
			return (size);
		}
		size += ret;
	}
	return (size - r->sv.size - 1);
}
