/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:37:13 by dkham             #+#    #+#             */
/*   Updated: 2022/12/02 17:32:30 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*new_src;
	unsigned char	*new_dst;

	if (dst == src)
		return (dst);
	new_src = (unsigned char *)src;
	new_dst = (unsigned char *)dst;
	if (dst < src)
	{
		while (len--)
			*new_dst++ = *new_src++;
	}
	else
	{
		while (len--)
			*(new_dst + len) = *(new_src + len);
	}
	return (dst);
}
