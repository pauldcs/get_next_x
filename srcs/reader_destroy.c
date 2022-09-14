/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:16:42 by pducos            #+#    #+#             */
/*   Updated: 2022/09/14 18:43:14 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_x.h"
#include <stdlib.h>

void	reader_destroy(t_reader *reader)
{
	if (reader->sv.str)
		free((void *)reader->sv.str);
}
