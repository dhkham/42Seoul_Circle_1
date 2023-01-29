/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:29:16 by dkham             #+#    #+#             */
/*   Updated: 2023/01/29 17:07:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s, char const *s2)
{
	char	*join;
	size_t	s_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s_len = ft_strlen(s);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * ((s_len + s2_len) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s_len + s2_len)
	{
		if (i < s_len)
			join[i] = s[i];
		else
			join[i] = s2[j++];
		i++;
	}
	join[i] = '\0';
	return (join);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str++) != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	if (s_len < len || s_len - start < len)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}