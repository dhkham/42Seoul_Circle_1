/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:37:52 by dkham             #+#    #+#             */
/*   Updated: 2022/11/25 14:13:11 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*unsigned_s1;
	unsigned char	*unsigned_s2;

	unsigned_s1 = (unsigned char *)s1;
	unsigned_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*unsigned_s1 != *unsigned_s2)
			return (*unsigned_s1 - *unsigned_s2);
		unsigned_s1++;
		unsigned_s2++;
	}
	return (0);
}
