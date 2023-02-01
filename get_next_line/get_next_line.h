/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:27:39 by dkham             #+#    #+#             */
/*   Updated: 2023/02/01 21:49:42 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_dlist
{
	int				fd;
	char			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*find_fd_node(int fd, t_list **head);
char	*read_line(t_list *cur_ptr, t_list *head, char *buf);
char	*make_line(t_list *cur_ptr, t_list **head, char *buf, \
ssize_t read_size);
void	*remove_cur_ptr(t_list *cur_ptr, t_list **head);
char	*ft_strjoin(char const *s, char const *s2);
int		check_slen(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif