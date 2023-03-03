/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/03 22:25:16 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_pdeque *ps)
{
	// use quick sort

	if (is_sorted(ps->a))		// if stack a is sorted
		return ;
	if (ps->a->cnt == 2)		// if stack a has 2 elements
	{
		if (ps->a->front->num > ps->a->rear->num)
			command(ps, "sa");
	}
	else if (ps->a->cnt == 3)	// if stack a has 3 elements
		sort_three(ps);
	else if (ps->a->cnt == 4) 	// if stack a has 4 elements
		sort_four(ps);
	else if (ps->a->cnt == 5)	// if stack a has 5 elements
		sort_five(ps);
	else					 	// if stack a has more than 5 elements
		quick_sort(ps);
	return ;
}

void	sort_three(t_pdeque *ps)
{
	int		a;
	int		b;
	int		c;

	a = ps->a->front->num;
	b = ps->a->front->next->num;
	c = ps->a->front->next->next->num;
	if (a > b && b > c) // a: 3, b: 2, c: 1
	{
		command(ps, "rra"); // 1 3 2
		command(ps, "rra"); // 2 1 3 내가 수정함
		command(ps, "sa"); // 1 2 3
		//command(ps, "sa"); // 원래 코드
	}
	else if (a > b && b < c && c > a) // a: 2, b: 1, c: 3
		command(ps, "sa"); // 1 2 3
	else if (a > b && b < c && c < a) // a: 3, b: 1, c: 2
		command(ps, "ra"); // 1 2 3
	else if (a < b && b > c && c > a) // a: 1, b: 3, c: 2
	{
		command(ps, "sa"); // 3 1 2
		command(ps, "ra"); // 1 2 3 내가 수정함
		//command(ps, "rra"); // 원래 코드
	}
	else if (a < b && b > c && c < a)
		command(ps, "rra");
}

void	sort_four(t_pdeque *ps)
{
	int		i;
	int		pivot;
	t_node	*tmp;

	i = 0;
	pivot = find_pivot(ps->a);
	while (i < 2)
	{
		tmp = ps->a->front;
		while (tmp)
		{
			if (tmp->num < pivot)
			{
				command(ps, "pb");
				break ;
			}
			command(ps, "ra");
			tmp = tmp->next;
		}
		i++;
	}
	sort_three(ps);
	command(ps, "pa");
	command(ps, "ra");
}

/* Here is the explanation for the code above:
1. 2 is the size of the stack (a) which is divided into 2 parts
2. The pivot is found
3. We iterate through the stack (a) until the number is less than the pivot
4. If the number is less than the pivot, then we push it to the stack (b)
5. If the number is greater than the pivot, then we rotate the stack (a)
6. We iterate through the stack (a) until we find the number that is less than the pivot
7. If the number is less than the pivot, then we push it to the stack (b)
8. If the number is greater than the pivot, then we rotate the stack (a)
9. The stack (b) is sorted with the help of the function sort_three           ????????????????????????뭔말이지
10. We push the number from the stack (b) to the stack (a) and rotate the stack (a)
11. We repeat the same steps in the loop until the stack (a) is sorted */

void	sort_five(t_pdeque *ps)
{
	int		i;
	int		pivot;
	t_node	*tmp;

	i = 0;
	pivot = find_pivot(ps->a);
	while (i < 2)
	{
		tmp = ps->a->front;
		while (tmp)
		{
			if (tmp->num < pivot)
			{
				command(ps, "pb");
				break ;
			}
			command(ps, "ra");
			tmp = tmp->next;
		}
		i++;
	}
	sort_three(ps);
	command(ps, "pa");
	command(ps, "pa");
}

// quicksort with two pivots
void	quick_sort(t_pdeque *ps)
{
	int		i;
	int		pivot;
	t_node	*tmp;

	i = 0;
	pivot = find_pivot(ps->a);
	while (i < 2)
	{
		tmp = ps->a->front;
		while (tmp)
		{
			if (tmp->num < pivot)
			{
				command(ps, "pb");
				break ;
			}
			command(ps, "ra");
			tmp = tmp->next;
		}
		i++;
	}
	quick_sort(ps);
	command(ps, "pa");
	command(ps, "pa");
}
// typedef struct s_pdeque
// {
// 	unsigned int	cnt; 
// 	struct s_deque	*a; 
// 	struct s_deque	*b;
// }	t_pdeque;

int		find_pivot(t_pdeque *ps)
{
	int		i;
	int		j;
	int		tmp;
	int		*arr;

	i = 0;
	j = 0;
	arr = (int *)malloc(sizeof(int) * ps->cnt);
	while (i < ps->cnt)
	{
		arr[i] = ps->a->front->num;    		// 오류  !!!! 
		ps->a->front = ps->a->front->next;  // 오류  !!!! 
		i++;
	}
	while (j < ps->cnt - 1)
	{
		i = 0;
		while (i < ps->cnt - 1)
		{
			if (arr[i] > arr[i + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
	return (arr[ps->cnt / 2]);
}
