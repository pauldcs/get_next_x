/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:42 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 23:22:22 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_reader.h"
#include <stdlib.h>

void	reader_destroy(t_reader *reader)
{
	if (reader->sv.buf)
		free((void *)reader->sv.buf);
}
