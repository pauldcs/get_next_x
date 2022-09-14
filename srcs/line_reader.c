/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:17:02 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 23:23:29 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_reader.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool	init_buf(t_reader *r, uint8_t **buf, size_t *size)
{	
	if (r->sv.buf)
	{
		*buf = (uint8_t *)r->sv.buf;
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

static bool	search_char(t_reader *r, int c, uint8_t *buf, size_t len)
{
	uint8_t	*ptr;
	size_t	n;

	ptr = buf + r->checked;
	n = len - r->checked;
	while (n--)
	{
		r->checked++;
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
	return (false);
}

ssize_t	line_reader(uint8_t **buf, int c, t_reader *r)
{
	size_t	size;
	int		ret;

	if (!init_buf(r, buf, &size))
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
			return (size);
		size += ret;
	}
	return (size - r->sv.size - 1);
}
