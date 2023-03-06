/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/06 22:25:33 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 지우기
#include <stdio.h>

void	push_swap(t_pdeque *pd)
{
	// greedy algorithm
	
	// rotate, push만 사용
	// deque b의 모든 값에 대해 count_ra값을 구한다. (ra를 몇번 해야 b의 값을 a에 push할 수 있는지)
	// e.g., a: 1 2 3 5 8 | b: 7 이면, count_ra = 4 (=> ra 4번 해줘야만 5, 8 사이에 7이 들어감)
	// count_ra가 a의 원소 수 절반보다 크면 rra가 더 효율적이다!
	// 마찬가지 원리로 count_rb도 구한다. (b 원소 수 절반보다 크면 rrb가 더 효율적)
	
	// 
	// ??
	
}

// void	push_swap(t_pdeque *pd)
// {
// 	int		i;
// 	t_node	*tmp_node;
// 	int		*tmp_arr;
// 	int		s_pivot;
// 	int		b_pivot;

// 	i = 0;
// 	tmp_node = pd->a->front;
// 	if (is_sorted(pd->a))
// 		return ;
// 	tmp_arr = (int *)malloc(sizeof(int) * pd->a->cnt);
// 	while (i < pd->a->cnt)
// 	{
// 		tmp_arr[i] = tmp_node->num;
// 		tmp_node = tmp_node->next;
// 		i++;
// 	}
// 	// loop thru tmp_arr and print values
// 	i = 0;
// 	while (i < pd->a->cnt)
// 	{
// 		printf("before sorting: %d\n", tmp_arr[i]);
// 		i++;
// 	}
// 	bubblesort(tmp_arr, pd->a->cnt);
// 	i = 0;
// 	while (i < pd->a->cnt)
// 	{
// 		printf("after sorting: %d\n", tmp_arr[i]);
// 		i++;
// 	}
// 	s_pivot = tmp_arr[pd->a->cnt / 3];
// 	b_pivot = tmp_arr[pd->a->cnt / 3 * 2];
// 	printf("s_pivot: %d, b_pivot: %d\n", s_pivot, b_pivot);
// 	free(tmp_arr);
// 	quick_sort(pd, s_pivot, b_pivot);
// 	sort_three(pd);
// 	// print deque a and b
// 	while (pd->a->front)
// 	{
// 		printf("a: %d\n", pd->a->front->num);
// 		pd->a->front = pd->a->front->next;
// 	}
// 	while (pd->b->front)
// 	{
// 		printf("b: %d\n", pd->b->front->num);
// 		pd->b->front = pd->b->front->next;
// 	}
// 	//btoa(pd);
// 	return ;
// }

// void	bubblesort(int *tmp_arr, int a_len)
// {
// 	int	i;
// 	int	j;
// 	int	tmp;
// 	int	tmp_arr_len;

// 	i = 0;
// 	tmp_arr_len = a_len;
// 	while (i < tmp_arr_len - 1)
// 	{
// 		j = 0;
// 		while (j < tmp_arr_len - i - 1)
// 		{
// 			if (tmp_arr[j] > tmp_arr[j + 1])
// 			{
// 				tmp = tmp_arr[j];
// 				tmp_arr[j] = tmp_arr[j + 1];
// 				tmp_arr[j + 1] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// // if bigger than b_pivot, leave it in a
// // if equal or less than b_pivot, push it to b
// // in b, if equal or less than s_pivot, use command "ra"
// // leave three elements and push the rest to b
// void	quick_sort(t_pdeque *pd, int pivot1, int pivot2)
// {
// 	t_node	*tmp_node;
// 	int		i;

// 	i = 0;
// 	tmp_node = pd->a->front;
// 	while (i < pd->a->cnt)
// 	{
// 		if (tmp_node->num > pivot2)
// 			tmp_node = tmp_node->next;
// 		else if (tmp_node->num <= pivot2)
// 		{
// 			command(pd, "pb");
// 			if (tmp_node->num <= pivot1)
// 				command(pd, "ra");
// 		}
// 		i++;
// 	}
// 	while (pd->a->cnt > 3)
// 	{
// 		command(pd, "pb");
// 	}
// 	return ;
// }

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
