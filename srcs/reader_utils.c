/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:22:14 by pducos            #+#    #+#             */
/*   Updated: 2022/10/03 00:12:11 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

bool	r_alloc(void **ptr, size_t size)
{
	char	*s;

	*ptr = malloc(size);
	if (!*ptr)
		return (false);
	s = *ptr;
	while (size--)
		*(s++) = 0x00;
	return (true);
}

bool	r_realloc(void **buf, size_t *cap, size_t len, size_t new_cap)
{
	void	*new_buf;

	new_buf = NULL;
	if (!r_alloc(&new_buf, new_cap))
		return (false);
	r_memcpy(new_buf, *buf, len);
	free(*buf);
	*buf = new_buf;
	*cap = new_cap;
	return (true);
}

void	*r_memcpy(void *dst, const void *src, size_t n)
{
	uint8_t	*tmp;

	tmp = dst;
	while (n--)
		*(tmp++) = *(uint8_t *)src++;
	return (dst);
}
