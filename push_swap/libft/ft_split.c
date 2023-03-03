/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:53:24 by dkham             #+#    #+#             */
/*   Updated: 2022/12/02 17:34:23 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putword(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_free_double_ptr(char **list)
{
	size_t	j;

	j = 0;
	while (list[j])
	{
		free(list[j]);
		j++;
	}
	free(list);
	return (NULL);
}

size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || \
		(s[i] == c && s[i + 1] != c && s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	wordstart;

	i = 0;
	j = 0;
	result = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!result)
		return (NULL);
	while (i < ft_countword(s, c))
	{
		while (s[j] == c)
			j++;
		wordstart = j;
		while (s[j] != c && s[j])
			j++;
		result[i] = ft_putword(&s[wordstart], j - wordstart);
		if (result[i++] == 0)
			return (ft_free_double_ptr(result));
	}
	result[i] = NULL;
	return (result);
}
