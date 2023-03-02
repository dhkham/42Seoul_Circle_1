/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:18:15 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 21:56:23 by dkham            ###   ########.fr       */
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
	node = dequeue(from, FRONT);
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
	node1 = dequeue(st, FRONT);
	node2 = dequeue(st, FRONT);
	enqueue(st, FRONT, node1);
	enqueue(st, FRONT, node2);
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
	node = dequeue(st, rear);
	enqueue(st, !rear, node);
	return (1);
}

// is_rear function ???
// int	is_rear(enum e_rear rear)
// {
// 	if (rear == 0)
// 		return (0);
// 	else if (rear == 1)
// 		return (1);
// }

t_node	*dequeue(t_deque *st, enum e_rear rear)
{
	t_node	*node;  // 1. deque 함수가 노드를 반환할 node를 선언한다.

	if (st->cnt < 1)  // 2. st->cnt가 1보다 작다면, st에 저장된 노드가 없으므로 명령어 처리를 X한다.
		return (0);  // 3. node를 반환한다.
	if (rear) // change to if statement 	: node = rear ? st->rear : st->front;
		node = st->rear;  // 4. node에 st->rear를 대입한다.
	else
		node = st->front;  // 5. node에 st->front를 대입한다.
	if (st->cnt == 1)  // 6. st->cnt가 1이면, st에 저장된 노드는 1개이다.
	{
		st->front = 0;  // 7. st->front에 NULL을 대입한다.
		st->rear = 0;  // 8. st->rear에 NULL을 대입한다.
	}
	else if (rear)  // 9. st->cnt가 1보다 크고, rear가 참이면, st에 저장된 노드는 2개 이상이다.
	{
		st->rear = node->prev;  // 10. st->rear에 node->prev를 대입한다.
		st->rear->next = 0;  // 11. st->rear->next에 NULL을 대입한다.
	}
	else  // 12. st->cnt가 1보다 크고, rear가 거짓이면, st에 저장된 노드는 2개 이상이다.
	{
		st->front = node->next;  // 13. st->front에 node->next를 대입한다.
		st->front->prev = 0;  // 14. st->front->prev에 NULL을 대입한다.
	}
	st->cnt--;  // 15. st->cnt를 1 감소시킨다.
	return (node);  // 16. node를 반환한다.
}

void	enqueue(t_deque *st, enum e_rear rear, t_node *node)
{
	if (st->cnt == 0) // If the deque is empty
	{
		st->front = node; // The front and rear of the deque are the node
		st->rear = node;
	}
	else if (rear) // If the rear is true
	{
		st->rear->next = node; // The next pointer of the rear is the node
		node->prev = st->rear; // The prev pointer of the node is the rear
		st->rear = node; // The rear is the node
	}
	else // If the rear is false
	{
		st->front->prev = node; // The prev pointer of the front is the node
		node->next = st->front; // The next pointer of the node is the front
		st->front = node; // The front is the node
	}
	st->cnt++; // Increment the count of nodes in the deque
}
