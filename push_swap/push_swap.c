/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/07 22:25:47 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// calculate command_count for all elements in b
// get the minimum command_count and execute commands for the element
// e.g., a: 1 5 8 | b: 7 6 2 3
// 7의 경우: count_ra = 2 (=> ra 2번 해줘야만 5, 8 사이에 7이 들어감) | count_rb = 0 (맨 위라서 바로 pb 가능)          (count_ra/rb 중 큰 값: 2)=>  ra ra pa
// 6의 경우: count_ra = 2 (=> ra 2번 해줘야만 5, 8 사이에 6이 들어감) | count_rb = 1 (맨 위가 아니라서 rb 1번 해줘야함)   (count_ra/rb 중 큰 값: 2)=> rr ra pa
// 2의 경우: count_ra = 1 (=> ra 1번 해줘야만 5, 8 사이에 2가 들어감) | count_rb = 2 (맨 위가 아니라서 rb 2번 해줘야함)   (count_ra/rb 중 큰 값: 2)=> rr rb pa
// 3의 경우: count_ra = 1 (=> ra 1번 해줘야만 5, 8 사이에 3이 들어감) | count_rb = 3 (맨 위가 아니라서 rrb 1번 해줘야함)  (count_ra/rb 중 큰 값: 3)=> ra rrb pa
// count_rb: how many rb is needed before using pa
void	push_swap(t_pdeque *pd)
{
	int		isrra_isrrb[2];
	int		count_arr[3];
	int		i;
	t_node	*curr_b;
	int		*count_cmd_arr;

	i = 0;
	while (pd->a->cnt > 3)	// push all elements to b until a->cnt == 3
		command(pd, "pb");
	sort_three(pd);	// sort 3 elements in a
	curr_b = pd->b->front; // make a temporary pointer that indicates the current node
	count_cmd_arr = (int *)malloc(sizeof(int) * pd->b->cnt);
	while (curr_b != NULL)
	{
		count_arr[0] = get_count_ra(pd, curr_b, isrra_isrrb);
		count_arr[1] = get_count_rb(pd, curr_b, isrra_isrrb);
		if (count_arr[0] > count_arr[1])
			count_cmd_arr[i++] = count_arr[0];
		else
			count_cmd_arr[i++] = count_arr[1];
		curr_b = curr_b->next;
	}
	// count_cmd_arr: how many commands are needed to push the element to a for all elements in b
	// execute_cmd
	execute_cmd(pd, count_cmd_arr);
	free(count_cmd_arr);
}

void	execute_cmd(t_pdeque *pd, int *count_cmd_arr)
{
// find index for minimal value in array(=min_idx) in count_cmd_arr
// execute commands for the element in b that has the min_idx

	// find min_idx
	int		min_idx;
	int		i;
	int		min;

	i = 0;
	min = count_cmd_arr[0];
	min_idx = 0;
	while (i < pd->b->cnt)
	{
		if (min > count_cmd_arr[i])
		{
			min = count_cmd_arr[i];
			min_idx = i;
		}
		i++;
	}
	
	// execute commands for the element in b that has the min_idx
	
}

int	get_count_ra(t_pdeque	*pd, t_node *curr_b, int *isrra_isrrb[2])
{
	int		count_ra;
	int		b_front_val;
	t_node	*tmp;

	count_ra = 0;
	tmp = pd->a->front;	// use temporary pointer to iterate through a
	while (tmp->num < curr_b->num) 	// find first value in a that is bigger than b_front_val
	{
		count_ra++;
		tmp = tmp->next;
	}
	free(tmp);
	if (count_ra >= pd->a->cnt / 2 + 1)
	{
		*isrra_isrrb[0] = 1; // rra
		count_ra = pd->a->cnt - count_ra;
	}
	else
		*isrra_isrrb[0] = 0; // ra
	return (count_ra);
}

int	get_count_rb(t_pdeque	*pd, t_node *curr_b, int *isrra_isrrb[2])
{
	int		count_rb;
	t_node	*tmp;

	count_rb = 0;
	if (curr_b == pd->b->front) 	// if the value is in the front, count_rb = 0
		return (count_rb);
	else // if the value is not in the front, count_rb = how many rb is needed before using pa
	{
		count_rb = 1;
		tmp = curr_b;
		while (tmp->prev != pd->b->front)	// calculate the distance between tmp and the front of b
		{
			count_rb++;
			tmp = tmp->prev;
		}
		free(tmp);
		if (count_rb >= pd->b->cnt / 2 + 1)
		{
			*isrra_isrrb[1] = 1; // rrb
			count_rb = pd->b->cnt - count_rb;
		}
		else
			*isrra_isrrb[1] = 0; // rb
	}
	return (count_rb);
}

// sort three elements in stack a
void	sort_three(t_pdeque *pd)
{
	int		a;
	int		b;
	int		c;

	a = pd->a->front->num;
	b = pd->a->front->next->num;
	c = pd->a->rear->num; //c = pd->a->front->next->next->num;
	if (a < b && b > c && c > a) // a: 1, b: 3, c: 2
	{
		command(pd, "sa"); // 3 1 2
		command(pd, "ra"); // 1 2 3
	}
	else if (a > b && b < c && c > a) // a: 2, b: 1, c: 3
		command(pd, "sa"); // 1 2 3
	else if (a < b && b > c && c < a) // a: 2, b: 3, c: 1
		command(pd, "rra"); // 1 2 3
	else if (a > b && b < c && c < a) // a: 3, b: 1, c: 2
		command(pd, "ra"); // 1 2 3
	else if (a > b && b > c) // a: 3, b: 2, c: 1
	{
		command(pd, "sa"); // 2 3 1
		command(pd, "rra"); // 1 2 3
	}
}

