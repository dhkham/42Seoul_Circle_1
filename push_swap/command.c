/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/03/11 20:52:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	command(t_pdeque *pd, char *cmd)
{
	if (ft_strncmp(cmd, "pa", 3) == 0)
		return (push(pd->b, pd->a));
	else if (ft_strncmp(cmd, "pb", 3) == 0)
		return (push(pd->a, pd->b));
	else if (ft_strncmp(cmd, "sa", 3) == 0)
		return (swap(pd->a));
	else if (ft_strncmp(cmd, "sb", 3) == 0)
		return (swap(pd->b));
	else if (ft_strncmp(cmd, "ss", 3) == 0)
		return (swap(pd->a) && swap(pd->b));
	else if (ft_strncmp(cmd, "ra", 3) == 0)
		return (rotate(pd->a, FRONT));
	else if (ft_strncmp(cmd, "rb", 3) == 0)
		return (rotate(pd->b, FRONT));
	else if (ft_strncmp(cmd, "rr", 3) == 0)
		return (rotate(pd->a, FRONT) && rotate(pd->b, FRONT));
	else if (ft_strncmp(cmd, "rra", 4) == 0)
		return (rotate(pd->a, REAR));
	else if (ft_strncmp(cmd, "rrb", 4) == 0)
		return (rotate(pd->b, REAR));
	else if (ft_strncmp(cmd, "rrr", 4) == 0)
		return (rotate(pd->a, REAR) && rotate(pd->b, REAR));
	ft_putstr_fd("Error\n", 2);
	exit(-1);
}

int	push(t_deque *from, t_deque *to)
{
	int		val;
	int		is_error;

	if (from->cnt < 1)
		return (0);
	is_error = 0;
	val = delete_front(from, &is_error);
	if (is_error)
		return (0);
	insert_front(to, val);
	return (1);
}

int	swap(t_deque *deque)
{
	int		val1;
	int		val2;
	int		is_error1;
	int		is_error2;

	if (deque->cnt < 2)
		return (0);
	is_error1 = 0;
	is_error2 = 0;
	val1 = delete_front(deque, &is_error1);
	val2 = delete_front(deque, &is_error2);
	if (is_error1 || is_error2)
		return (0);
	insert_front(deque, val1);
	insert_front(deque, val2);
	return (1);
}

int	rotate(t_deque *deque, enum e_rear is_rear)
{
	int		val;
	int		is_error;

	if (deque->cnt < 1)
		return (0);
	if (is_rear) // rra, rrb, rrr
	{
		val = delete_rear(deque, &is_error);
		if (is_error)
			return (0);
		insert_front(deque, val);
	}
	else         // ra, rb, rr
	{
		val = delete_front(deque, &is_error);
		if (is_error)
			return (0);
		insert_rear(deque, val);
	}
	return (1);
}
