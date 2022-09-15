/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:42 by pducos            #+#    #+#             */
/*   Updated: 2022/09/15 12:35:14 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_reader.h"
#include <stdlib.h>

void	reader_destroy(t_reader *reader)
{
	if (reader->save.buf)
		free((void *)reader->save.buf);
}
