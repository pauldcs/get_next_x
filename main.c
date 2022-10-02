/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducos <pducos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:08:32 by pducos            #+#    #+#             */
/*   Updated: 2022/10/03 00:33:33 by pducos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/reader.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	unsigned char	*line;
	ssize_t			ret;
	t_reader		*r;

	line = NULL;
	if (ac == 2)
	{
		r = reader_init(av[1]);
		if (r)
		{
			while ((ret = reader(&line, r, "\n")) != -1)
			{
				//printf ("%s\n", line);
				write (1, line, ret);
				write (1, "\n", 1);
				free(line);
			}
			reader_destroy(r);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
