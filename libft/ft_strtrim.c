/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:38:50 by dkham             #+#    #+#             */
/*   Updated: 2022/12/01 13:12:45 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_len;
	char	*str;

	str = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	s1_len = ft_strlen(s1);
	while (i < s1_len && ft_strchr(set, s1[i]))
		i++;
	while (i < s1_len && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	str = (char *)malloc(sizeof(char) * (s1_len - i) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[i], s1_len - i + 1);
	return (str);
}
