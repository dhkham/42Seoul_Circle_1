/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:27:15 by dkham             #+#    #+#             */
/*   Updated: 2023/02/04 14:58:26 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	while (cur) // head가 빈 linked list가 아닐 때 loop
	{
		if (cur->fd == fd) // fd가 이미 저장되어 있으면 해당 fd의 linked list 노드를 가리키는 포인터 return
			return (cur);
		prior = cur;
		cur = cur->next;
	}
	if (cur == NULL) // 해당 fd 노드 없을 경우 새 노드 생성
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
		read_size = read(cur->fd, buf, BUFFER_SIZE); //fd에서 nbyte만큼 읽어와 buf에 저장
		if (read_size == -1)   //1. read error
			return (remove_cur_ptr(cur, head));
		if (read_size == 0)    //2. EOF
		{
			if (cur->data == NULL || !*(cur->data)) // 아예 빈 파일일 경우
				return (remove_cur_ptr(cur, head));
			return (make_line(cur, head));
		}
		buf[read_size] = '\0'; //3. 정상적인 read 실행 시
		tmp = cur->data;
		cur->data = ft_strjoin(cur->data, buf); // data에 buf를 붙여 cur->data에 저장
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

	lb = ft_strchr(cur->data, '\n'); // '\n'이 있는 위치를 가리키는 포인터
	if (lb == NULL) // 파일에 '\n'이 없는 경우 (예. hello(EOF)))
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
	if (cur == NULL || *head == NULL) // 둘 중 하나라도 NULL이면 NULL 리턴
		return (NULL);
	if (cur->prev != NULL) 	// 현 노드가 첫 노드가 아니면 이전 노드의 next가 현 노드의 next를 가리키게 함
		cur->prev->next = cur->next;
	if (cur->next != NULL) // 현 노드가 마지막 노드가 아니면 다음 노드의 prev가 현 노드의 prev를 가리키게 함
		cur->next->prev = cur->prev;
	if (cur == *head) // 현 노드가 첫 노드면(혹은 노드가 하나면)
		*head = cur->next;
	free(cur->data);
	cur->data = NULL; // free 후 NULL로 초기화
	free(cur);
	return (NULL);
}
