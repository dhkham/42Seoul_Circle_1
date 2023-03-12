/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/03/12 19:53:36 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	command(t_pdeque *pd, char *cmd)
{
	if (ft_strncmp(cmd, "pa", 3) == 0)
		return (push(pd->b, pd->a, 0));
	else if (ft_strncmp(cmd, "pb", 3) == 0)
		return (push(pd->a, pd->b, 1));
	else if (ft_strncmp(cmd, "sa", 3) == 0)
		return (swap(pd->a, 0));
	else if (ft_strncmp(cmd, "sb", 3) == 0)
		return (swap(pd->b, 1));
	else if (ft_strncmp(cmd, "ss", 3) == 0)
		return (exec_ss(pd, 2)); //return (swap(pd->a) && swap(pd->b));
	// else if (ft_strncmp(cmd, "ra", 3) == 0)
	// 	return (rotate(pd->a, FRONT));
	// else if (ft_strncmp(cmd, "rb", 3) == 0)
	// 	return (rotate(pd->b, FRONT));
	// else if (ft_strncmp(cmd, "rr", 3) == 0)
	// 	return (rotate(pd->a, FRONT) && rotate(pd->b, FRONT));
	// else if (ft_strncmp(cmd, "rra", 4) == 0)
	// 	return (rotate(pd->a, REAR));
	// else if (ft_strncmp(cmd, "rrb", 4) == 0)
	// 	return (rotate(pd->b, REAR));
	// else if (ft_strncmp(cmd, "rrr", 4) == 0)
	// 	return (rotate(pd->a, REAR) && rotate(pd->b, REAR));
	else if (ft_strncmp(cmd, "ra", 3) == 0)
		return (rotate(pd->a, FRONT, 0));
	else if (ft_strncmp(cmd, "rb", 3) == 0)
		return (rotate(pd->b, FRONT, 1));
	else if (ft_strncmp(cmd, "rr", 3) == 0)
		return (exec_rr(pd, FRONT, 2)); //return (rotate(pd->a, FRONT) && rotate(pd->b, FRONT));
	else if (ft_strncmp(cmd, "rra", 4) == 0)
		return (rotate(pd->a, REAR, 0));
	else if (ft_strncmp(cmd, "rrb", 4) == 0)
		return (rotate(pd->b, REAR, 1));
	else if (ft_strncmp(cmd, "rrr", 4) == 0)
		return (exec_rr(pd, REAR, 2)); //return (rotate(pd->a, REAR) && rotate(pd->b, REAR));
	ft_putstr_fd("Error\n", 2);
	exit(-1);
}

int	push(t_deque *from, t_deque *to, int pa_pb)
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
	if (pa_pb == 0)
		ft_putstr_fd("pa\n", 1);
	else
		ft_putstr_fd("pb\n", 1);
	return (1);
}

int	swap(t_deque *deque, int sa_sb)
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
	if (sa_sb == 0)
		ft_putstr_fd("sa\n", 1);
	else if (sa_sb == 1)
		ft_putstr_fd("sb\n", 1);
	return (1);
}

int	exec_ss(t_pdeque *pd, int ss)
{
	swap(pd->a, ss);
	swap(pd->b, ss);
	ft_putstr_fd("ss\n", 1);
	return (1);
}

int	rotate(t_deque *deque, enum e_rear is_rear, int ra_rb)
{
	int		val;
	int		is_error;

	is_error = 0;
	if (deque->cnt < 2)
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
	if (is_rear == 0 && ra_rb == 0)
		ft_putstr_fd("ra\n", 1);
	else if (is_rear == 0 && ra_rb == 1)
		ft_putstr_fd("rb\n", 1);
	else if (is_rear == 1 && ra_rb == 0)
		ft_putstr_fd("rra\n", 1);
	else if (is_rear == 1 && ra_rb == 1)
		ft_putstr_fd("rrb\n", 1);
	return (1);
}

int	exec_rr(t_pdeque *pd, enum e_rear is_rear, int rr)
{
	if (is_rear == REAR)
	{
		rotate(pd->a, REAR, rr);
		rotate(pd->b, REAR, rr);
		ft_putstr_fd("rrr\n", 1);
	}
	else if (is_rear == FRONT)
	{
		rotate(pd->a, FRONT, rr);
		rotate(pd->b, FRONT, rr);
		ft_putstr_fd("rr\n", 1);
	}
	return (1);
}
