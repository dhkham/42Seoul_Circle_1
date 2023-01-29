/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:26:52 by dkham             #+#    #+#             */
/*   Updated: 2023/01/29 21:28:38 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list	*fd_storage;
	t_list			*cur_ptr;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cur_ptr = find_fd_in_storage(fd, &fd_storage); // linked list로 각 fd별로 저장
	line = make_line(cur_ptr, fd_storage);
	return (line);
}

t_list	*find_fd_in_storage(int fd, t_list **fd_storage)
{
	t_list	*cur_ptr;
	t_list	*temp;

	temp = NULL;
	cur_ptr = *fd_storage;
	while (cur_ptr) // fd_storage가 빈 linked list가 아닐 때 loop
	{
		if (cur_ptr->fd == fd) // fd가 이미 저장되어 있으면 해당 fd의 linked list를 가리키는 포인터 return
			return (cur_ptr);
		if (cur_ptr->next == NULL) // cur_ptr이 마지막 linked list가리킬 경우 temp가 마지막 노드 가리킴
			temp = cur_ptr;
		cur_ptr = cur_ptr->next;
	}
	if (cur_ptr == NULL) // fd_storage가 빈 linked list일 경우 새로운 linked list 노드 생성
	{
		cur_ptr = (t_list *)malloc(sizeof(t_list));
		if (cur_ptr == NULL)
			return (NULL);
		*fd_storage = cur_ptr; // fd_storage가 새로 생성된 linked list를 가리키게 함
		cur_ptr->fd = fd;
		cur_ptr->data = NULL;
		cur_ptr->next = NULL;
		cur_ptr->prev = NULL;
	}
	return (cur_ptr);
}

char *make_line(t_list *cur_ptr, t_list *fd_storage) // line = NULL;
{
	char	*buf;
	char	*line;
	char	*new_line;
	char	*del;
	ssize_t	read_size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (1)
	{
		read_size = read(cur_ptr->fd, buf, BUFFER_SIZE);
		if (read_size == -1) // read error
			return (remove_cur_ptr(cur_ptr, &fd_storage));
		if (read_size == 0) // EOF
		{
			if (cur_ptr->data == NULL)
				return (NULL);
			line = ft_substr(cur_ptr->data, 0, ft_strlen(cur_ptr->data));
			free(cur_ptr->data);
			cur_ptr->data = NULL;
			return (line);
		}
		buf[BUFFER_SIZE] = '\0';						// 정상적인 read 실행 시
		cur_ptr->data = ft_strjoin(cur_ptr->data, buf); // cur_ptr->data에 buf를 붙여 cur_ptr->data에 저장
		new_line = ft_strchr(cur_ptr->data, '\n');		// cur_ptr->data에 \n이 있는지 확인
		if (new_line)									// \n이 있을 경우
		{
			line = ft_substr(cur_ptr->data, 0, new_line - (cur_ptr->data) + 1); // \n까지의 문자열을 line에 저장
			del = cur_ptr->data;
			cur_ptr->data = ft_substr(cur_ptr->data, \
			(new_line - cur_ptr->data + 1), ft_strlen(cur_ptr->data));
			free(del);																			 // substr 하면 malloc 된 결과물이 cur_ptr->data에 저장되므로 del로 free
			return (line);																		 // ==> line은 free 안해도 되나?
		}
	}
	return (line);
}

void	*remove_cur_ptr(t_list *cur_ptr, t_list **fd_storage)
{
	if (cur_ptr == NULL || fd_storage == NULL) // 둘 중 하나라도 NULL이면 NULL 리턴
		return (NULL);
	if (cur_ptr->prev != NULL) 	// 현 노드가 첫 노드가 아니면 이전 노드의 next가 현 노드의 next를 가리키게 함
		cur_ptr->prev->next = cur_ptr->next;
	if (cur_ptr->next != NULL) // 현 노드가 마지막 노드가 아니면 다음 노드의 prev가 현 노드의 prev를 가리키게 함
		cur_ptr->next->prev = cur_ptr->prev;
	if (cur_ptr == *fd_storage) // 현 노드가 첫 노드면(혹은 노드가 하나면) fd_storage가 두번째 노드를 가리키게 함
		*fd_storage = cur_ptr->next;
	free(cur_ptr->data);
	cur_ptr->data = NULL; // free 후 NULL로 초기화
	free(cur_ptr);
	return (NULL);
}
