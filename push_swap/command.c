/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/03/06 20:20:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "stdio.h"
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
	ft_putstr_fd("Error", 2);
	exit(-1);
}

// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.
// a: 0 3 2 1 => a: 3 2 1 / b: 0

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

// sa (swap a): Swap the first 2 elements at the top of deque a.
// Do nothing if there is only one or no elements.
// a: 321 / b: 0 => a: 231 / b: 0

// sb (swap b): Swap the first 2 elements at the top of deque b.
// Do nothing if there is only one or no elements.

// ss : sa and sb at the same time.

int	swap(t_deque *deque)
{
	int		val1;
	int		val2;
	int		is_error1;
	int		is_error2;

	if (deque->cnt < 2)
		return (0);
	val1 = delete_front(deque, &is_error1);
	val2 = delete_front(deque, &is_error2);
	if (is_error1 || is_error2)
		return (0);
	insert_front(deque, val1);
	insert_front(deque, val2);
	return (1);
}

// ra (rotate a): Shift up all elements of deque a by 1.
// The first element becomes the last one.
// 3 2 1 0 -> 2 1 0 3

// rb (rotate b): Shift up all elements of deque b by 1.
// The first element becomes the last one.

// rr : ra and rb at the same time.

// rra (reverse rotate a): Shift down all elements of deque a by 1.
// The last element becomes the first one.
// 3 2 1 0 -> 0 3 2 1

// rrb (reverse rotate b): Shift down all elements of deque b by 1.
// The last element becomes the first one.

// rrr : rra and rrb at the same time.
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
