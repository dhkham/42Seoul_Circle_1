/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:53:04 by dkham             #+#    #+#             */
/*   Updated: 2023/03/05 16:26:56 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	checker(t_pdeque *pd)
{
	char	*cmd;

	cmd = get_next_line(0);
	while (cmd)
	{
		command(pd, cmd);
		// debug(pd); 
		cmd = get_next_line(0);
	}
	// if stack b is empty and stack a is sorted
	if (is_empty(pd->b) && is_sorted(pd->a))
		ft_putstr_fd(1, "OK\n");
	else
		ft_putstr_fd(1, "KO\n");
}
