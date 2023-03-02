/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 21:37:04 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	checker(t_pdeque *ps)
{
	char	*cmd;

	cmd = get_next_line(0);
	while (cmd)
	{
		command(ps, cmd);
		// debug(ps); 
		cmd = get_next_line(0);
	}
	// if stack b is empty and stack a is sorted
	if (is_empty(ps->b) && is_sorted(ps->a))
		ft_putstr_fd(1, "OK\n");
	else
		ft_putstr_fd(1, "KO\n");
}

void	push_swap(t_pdeque *ps)
{
 /* 정렬 로직 */
};