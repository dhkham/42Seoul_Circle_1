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
	char	*line;

	fd = open("two_lines_with_nl", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}

// char	*split_line(t_list *current_fd, t_list **head)
// {
// 	char	*line;
// 	char	*tmp;

// 	line = NULL;
// 	if (!(current_fd->backup && *(current_fd->backup)))
// 		return (remove_fd(current_fd, head));
// 	tmp = ft_strchr(current_fd->backup, '\n');
// 	if (tmp)
// 	{	
// 		*tmp = '\0';
// 		line = ft_strjoin(current_fd->backup, "\n");
// 		if (!line)
// 			return (remove_fd(current_fd, head));
// 		ft_strlcpy(current_fd->backup, tmp + 1, ft_strlen(tmp + 1) + 1);
// 		return (line);
// 	}
// 	else
// 	{
// 		line = ft_strjoin(current_fd->backup, "");
// 		if (!line)
// 			return (remove_fd(current_fd, head));
// 		remove_fd(current_fd, head);
// 		return (line);
// 	}
// }

// char	*read_line(int fd, t_list *current_fd, t_list **head, ssize_t read_size)
// {
// 	char			*line;
// 	char			*tmp;

// 	while (1)
// 	{
// 		read_size = read(fd, current_fd->read_buff, BUFFER_SIZE);
// 		if (read_size == 0)
// 		{
// 			line = split_line(current_fd, head);
// 			return (line);
// 		}
// 		if (read_size == -1)
// 			return (remove_fd(current_fd, head));
// 		current_fd->read_buff[read_size] = '\0';
// 		tmp = ft_strjoin(current_fd->backup, current_fd->read_buff);
// 		if (!tmp)
// 			return (remove_fd(current_fd, head));
// 		free(current_fd->backup);
// 		current_fd->backup = tmp;
// 		if (ft_strchr(current_fd->backup, '\n') != NULL)
// 		{
// 			line = split_line(current_fd, head);
// 			return (line);
// 		}
// 	}
// }

