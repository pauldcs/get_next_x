/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:17:02 by pducos            #+#    #+#             */
/*   Updated: 2022/10/03 00:24:10 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static bool	is_sep(char *sep, int c)
{
	while (*sep)
	{
		if (*sep == c)
			return (true);
		sep++;
	}
	return (false);
}

static bool	init_buf(t_reader *r, uint8_t **buf, size_t *size)
{	
	if (r->save.buf)
	{
		*buf = (uint8_t *)r->save.buf;
		*size = r->save.size;
		r->cap = *size;
	}
	else
	{
		if (!r_alloc((void **)buf, INITIAL_CAP + 1))
			return (false);
		r->cap = INITIAL_CAP;
		*size = 0;
	}
	return (true);
}

static bool	search_char(t_reader *r, char *sep, uint8_t *buf, size_t len)
{
	uint8_t	*ptr;
	size_t	n;

	ptr = buf + r->checked;
	n = len - r->checked;
	while (n--)
	{
		r->checked++;
		if (!is_sep(sep, *ptr) && ptr++)
			continue ;
		*ptr++ = '\0';
		len -= ptr - buf;
		if (len)
		{
			if (!r_alloc((void *)&r->save.buf, len)
				|| !r_memcpy((void *)r->save.buf, ptr, len))
				return (false);
			r->save.size = len;
		}
		return (true);
	}
	return (false);
}

ssize_t	reader(uint8_t **buf, t_reader *r, char *sep)
{
	size_t	size;
	int		ret;

	if (!init_buf(r, buf, &size))
		return (-1);
	r->save.buf = NULL;
	r->save.size = 0;
	r->checked = 0;
	while (!search_char(r, sep, *buf, size))
	{
		if (size >= r->cap
			&& !r_realloc((void *)buf, &r->cap, size, r->cap * 2))
			return (-1);
		ret = read(r->fd, &(*buf)[size], r->cap - size);
		if (ret == -1 || (!ret && !size))
			return (free(*buf), -1);
		else if (!ret)
			return (size);
		size += ret;
	}
	return (size - r->save.size - 1);
}
