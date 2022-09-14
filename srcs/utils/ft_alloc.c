/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 23:22:14 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 23:22:15 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
