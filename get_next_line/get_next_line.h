/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:27:39 by dkham             #+#    #+#             */
/*   Updated: 2023/01/29 18:17:48 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

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
t_list	*find_fd_in_storage(int fd, t_list **fd_storage);
char	*make_line(t_list *cur_fd);
void	make_line_from_data(t_list *cur_fd, char *buf, char **line, char **new, char **del);
char	*ft_strjoin(char const *s, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif