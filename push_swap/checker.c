/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:53:04 by dkham             #+#    #+#             */
/*   Updated: 2023/03/03 22:00:34 by dkham            ###   ########.fr       */
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
