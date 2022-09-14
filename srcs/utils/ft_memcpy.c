/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:45:59 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 23:46:02 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	uint8_t	*tmp;

	tmp = dst;
	while (n--)
		*(tmp++) = *(uint8_t *)src++;
	return (dst);
}
