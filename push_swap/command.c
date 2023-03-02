/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 20:55:31 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	command(t_pdeque *ps, char *cmd)
{
	if (ft_strncmp(cmd, "pa\n", 4) == 0)
		return (push(&ps->a, &ps->b));
	if (ft_strncmp(cmd, "pb\n", 4) == 0)
		return (push(&ps->b, &ps->a));
	if (ft_strncmp(cmd, "sa\n", 4) == 0)
		return (swap(&ps->a));
	if (ft_strncmp(cmd, "sb\n", 4) == 0)
		return (swap(&ps->b));
	if (ft_strncmp(cmd, "ss\n", 4) == 0)
		return (swap(&ps->a) && swap(&ps->b));
	if (ft_strncmp(cmd, "ra\n", 4) == 0)
		return (rotate(&ps->a, FRONT));
	if (ft_strncmp(cmd, "rb\n", 4) == 0)
		return (rotate(&ps->b, FRONT));
	if (ft_strncmp(cmd, "rr\n", 4) == 0)
		return (rotate(&ps->a, FRONT) && rotate(&ps->b, FRONT));
	if (ft_strncmp(cmd, "rra\n", 5) == 0)
		return (rotate(&ps->a, REAR));
	if (ft_strncmp(cmd, "rrb\n", 5) == 0)
		return (rotate(&ps->b, REAR));
	if (ft_strncmp(cmd, "rrr\n", 5) == 0)
		return (rotate(&ps->a, REAR) && rotate(&ps->b, REAR));
	ft_putstr_fd(2, "Error\n"); // 명령어를 찾을 수 없는 경우
	exit(-1);
}

// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.
// a: 0 3 2 1 => a: 3 2 1 / b: 0

int	push(t_deque *from, t_deque *to)
{
	t_node	*node;

	if (from->cnt < 1)
		return (0);  // 뺄 게 없으므로 명령어 처리 X
	node = deque(from, FRONT);
	enque(to, FRONT, node);
	return (1);
}

// sa (swap a): Swap the first 2 elements at the top of deque a.
// Do nothing if there is only one or no elements.
// a: 321 / b: 0 => a: 231 / b: 0

// sb (swap b): Swap the first 2 elements at the top of deque b.
// Do nothing if there is only one or no elements.

// ss : sa and sb at the same time.
int	swap(t_deque *st)
{
	t_node	*node1;
	t_node	*node2;

	if (st->cnt < 2)
		return (0);  // 뺄 게 없으므로 명령어 처리 X
	node1 = deque(st, FRONT);
	node2 = deque(st, FRONT);
	enque(st, FRONT, node1);
	enque(st, FRONT, node2);
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
int	rotate(t_deque *st, enum e_rear rear)
{
	t_node	*node;

	if (st->cnt < 1)
		return (0);  // 뺄 게 없으므로 명령어 처리 X
	node = deque(st, is_rear);
	enque(st, !rear, node);
	return (1);
}

// is_rear function ???
int	is_rear(enum e_rear rear)
{
	if (rear == 0)
		return (0);
	else if (rear == 1)
		return (1);
}

t_node	*deque(t_deque *st, enum e_rear rear)
{
	t_node	*node;

	if (st->cnt < 1)
		return (0);  // 뺄 게 없으므로 명령어 처리 X
	if (rear) // change to if statement 	: node = rear ? st->rear : st->front;
		node = st->rear;
	else
		node = st->front;
	if (st->cnt == 1)
	{
		st->front = 0;
		st->rear = 0;
	}
	else if (rear)
	{
		st->rear = node->prev;
		st->rear->next = 0;
	}
	else
	{
		st->front = node->next;
		st->front->prev = 0;
	}
	st->cnt--;
	return (node);
}

void	enque(t_deque *st, enum e_rear rear, t_node *node)
{
	if (st->cnt == 0)
	{
		st->front = node;
		st->rear = node;
	}
	else if (rear)
	{
		st->rear->next = node;
		node->prev = st->rear;
		st->rear = node;
	}
	else
	{
		st->front->prev = node;
		node->next = st->front;
		st->front = node;
	}
	st->cnt++;
}
