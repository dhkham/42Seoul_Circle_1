/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:57:16 by dkham             #+#    #+#             */
/*   Updated: 2023/01/30 20:19:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fcntl.h"
#include "stdio.h"

int	main(void)
{
	int		fd;
	int		fd2;
	char	*line;
	char	*line2;

	fd = open("nl", O_RDONLY);
	fd2 = open("nl2", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		line2 = get_next_line(fd2);
		printf("%s", line2);
		if (line == NULL && line2 == NULL)
			break ;
		free(line);
		free(line2);
	}
	return (0);
}
