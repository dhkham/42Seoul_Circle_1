/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:27:15 by dkham             #+#    #+#             */
/*   Updated: 2023/02/05 13:07:21 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*cur;
	char			*line;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cur = find_fd_node(fd, &head);
	if (cur == NULL)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (remove_cur_ptr(cur, &head));
	line = read_line(cur, &head, buf);
	free(buf);
	return (line);
}

t_list	*find_fd_node(int fd, t_list **head)
{
	t_list	*cur;
	t_list	*prior;

	cur = *head;
	prior = NULL;
	while (cur && cur->fd != fd)
	{
		prior = cur;
		cur = cur->next;
	}
	if (cur == NULL)
	{
		cur = (t_list *)malloc(sizeof(t_list));
		if (cur == NULL)
			return (NULL);
		if (*head == NULL)
			*head = cur;
		cur->fd = fd;
		cur->data = NULL;
		cur->prev = prior;
		cur->next = NULL;
		if (prior)
			prior->next = cur;
	}
	return (cur);
}

char	*read_line(t_list *cur, t_list **head, char *buf)
{
	ssize_t	read_size;
	char	*tmp;

	while (1)
	{
		read_size = read(cur->fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (remove_cur_ptr(cur, head));
		if (read_size == 0)
		{
			if (cur->data == NULL || !*(cur->data))
				return (remove_cur_ptr(cur, head));
			return (make_line(cur, head));
		}
		buf[read_size] = '\0';
		tmp = cur->data;
		cur->data = ft_strjoin(cur->data, buf);
		free(tmp);
		if (cur->data == NULL)
			return (remove_cur_ptr(cur, head));
		if (ft_strchr(cur->data, '\n'))
			return (make_line(cur, head));
	}
}

char	*make_line(t_list *cur, t_list **head)
{
	char	*line;
	char	*lb;

	lb = ft_strchr(cur->data, '\n');
	if (lb == NULL)
	{
		line = ft_strdup(cur->data);
		if (line == NULL)
			return (remove_cur_ptr(cur, head));
		remove_cur_ptr(cur, head);
		return (line);
	}
	else
	{
		*lb = '\0';
		line = ft_strjoin(cur->data, "\n");
		if (line == NULL)
			return (remove_cur_ptr(cur, head));
		ft_strlcpy(cur->data, lb + 1, ft_strlen(lb + 1) + 1);
		return (line);
	}
}

void	*remove_cur_ptr(t_list *cur, t_list **head)
{
	if (cur == NULL || *head == NULL)
		return (NULL);
	if (cur->prev != NULL)
		cur->prev->next = cur->next;
	if (cur->next != NULL)
		cur->next->prev = cur->prev;
	if (cur == *head)
		*head = cur->next;
	free(cur->data);
	cur->data = NULL;
	free(cur);
	return (NULL);
}
