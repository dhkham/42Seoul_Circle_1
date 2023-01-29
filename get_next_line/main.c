/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:57:16 by dkham             #+#    #+#             */
/*   Updated: 2023/01/29 16:07:19 by dkham            ###   ########.fr       */
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

	fd = open("two_lines_with_nl", O_RDONLY);
	fd2 = open("two_lines_with_nl", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		line2 = get_next_line(fd2);
		printf("%s", line);
		printf("%s", line2);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}