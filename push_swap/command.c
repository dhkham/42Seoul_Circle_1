/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/02/22 22:16:03 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	command(struct s_pushswap *ps, char *cmd)
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

int	push(t_stack *from, t_stack *to)
{
	t_node	*node;

	if (from->cnt < 1) return (0);  // 뺄 게 없으므로 명령어 처리 X
	node = deque(from, FRONT);
	enque(to, FRONT, node);
	return (1);
}

int	swap(t_stack *st)
{
	t_node	*node[2];

	if (st->cnt < 2) return (0);  // swap 할 게 없으므로 명령어 처리 X
	node[0] = deque(st, FRONT);
	node[1] = deque(st, FRONT);
	enque(st,FRONT, node[0]);
	enque(st,FRONT, node[1]);
	return (1);
}

int	rotate(t_stack *st, enum e_rear rear)
{
	  t_node *node;

		if (st->cnt < 1) return (0);  // 뺄 게 없으므로 명령어 처리 X
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

t_node	*deque(t_stack *st, enum e_rear rear)
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

void	enque(t_stack *st, enum e_rear rear, t_node *node)
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

// sa (swap a): Swap the first 2 elements at the top of deque a.
// Do nothing if there is only one or no elements.

// sb (swap b): Swap the first 2 elements at the top of deque b.
// Do nothing if there is only one or no elements.

// ss : sa and sb at the same time.

// pa (push a): Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.

// pb (push b): Take the first element at the top of a and put it at the top of b.
// Do nothing if a is empty.

// ra (rotate a): Shift up all elements of deque a by 1.
// The first element becomes the last one.

// rb (rotate b): Shift up all elements of deque b by 1.
// The first element becomes the last one.

// rr : ra and rb at the same time.

// rra (reverse rotate a): Shift down all elements of deque a by 1.
// The last element becomes the first one.

// rrb (reverse rotate b): Shift down all elements of deque b by 1.
// The last element becomes the first one.

// rrr : rra and rrb at the same time.