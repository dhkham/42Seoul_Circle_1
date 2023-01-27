/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:33:28 by dkham             #+#    #+#             */
/*   Updated: 2022/12/02 17:49:00 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
