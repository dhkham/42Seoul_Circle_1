/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/08 22:26:50 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// calculate command_count for all elements in b
// get the minimum command_count and execute commands for the element
// e.g., a: 1 5 8 | b: 7 6 2 3
// 7의 경우: count_ra = 2 (=> ra 2번 해줘야만 5, 8 사이에 7이 들어감) | count_rb = 0 (맨 위라서 바로 pb 가능)          (count_ra/rb 중 큰 값: 2)=>  ra ra pa
// 6의 경우: count_ra = 2 (=> ra 2번 해줘야만 5, 8 사이에 6이 들어감) | count_rb = 1 (맨 위가 아니라서 rb 1번 해줘야함)   (count_ra/rb 중 큰 값: 2)=> rr ra pa
// 2의 경우: count_ra = 1 (=> ra 1번 해줘야만 5, 8 사이에 2가 들어감) | count_rb = 2 (맨 위가 아니라서 rb 2번 해줘야함)   (count_ra/rb 중 큰 값: 2)=> rr rb pa      count_ra - count_rb 절대값만큼 rr해줘야 
// 3의 경우: count_ra = 1 (=> ra 1번 해줘야만 5, 8 사이에 3이 들어감) | count_rb = 1 (맨 위가 아니라서 rrb 1번 해줘야함)  (count_ra/rb 중 큰 값: 1)=> ra rrb pa  // count_ra - count_rb 절대값만큼 rr해줘야 

void	push_swap(t_pdeque *pd)
{
	int		*b_cmd_cnt;
	int		*count_ra_arr;
	int		i;

	i = 0;
	while (pd->a->cnt > 3)
		command(pd, "pb");
	sort_three(pd);
	while (1) // b->a로 다 옮길 때까지 무한 루프
	{
		b_cmd_cnt = (int *)malloc(sizeof(int) * pd->b->cnt); // b 원소 수만큼 커맨드 수 저장할 배열
		count_ra_arr = (int *)malloc(sizeof(int) * pd->b->cnt); // b 원소 수만큼 ra 수 저장할 배열
		get_cmd_cnt(pd, b_cmd_cnt, count_ra_arr); // b 모든 원소에 대해 커맨드 수 계산
		execute_cmd(pd, b_cmd_cnt, count_ra_arr); // 커맨드 수가 가장 작은 원소에 대해 커맨드 실행
		if (pd->b->cnt == 0) // 다 옮겼으면 루프 탈출
			break ;
		free(b_cmd_cnt);
		free(count_ra_arr);
	}
}

void	sort_three(t_pdeque *pd)
{
	int		a;
	int		b;
	int		c;

	a = pd->a->front->num;
	b = pd->a->front->next->num;
	c = pd->a->rear->num;
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

void	get_cmd_cnt(t_pdeque *pd, int *b_cmd_cnt, int *count_ra_arr)
{
	int		count_ra;
	int		count_rb;
	int		i;
	int		*is_rrab;

	count_ra = 0;
	count_rb = 0;
	i = 0;
	is_rrab = (int *)malloc(sizeof(int) * pd->b->cnt * 2);
	while (i < pd->b->cnt)
	{
		count_ra = get_count_ra(pd, pd->b->front);//, is_rrab);
		count_rb = get_count_rb(pd, pd->b->front);//, is_rrab);
		
		// from here
		// count_ra, count_rb is minus if rra/rrb is used!
		
		b_cmd_cnt[i] = count_ra + count_rb; // 확인
		count_ra_arr[i] = count_ra;
		i++;
	}
}

int	get_count_ra(t_pdeque	*pd, t_node *cur_b)//, int *is_rrab)
{
	int		count_ra;
	int		b_front_val;
	t_node	*tmp;

	count_ra = 0;
	tmp = pd->a->front;	// use temporary pointer to iterate through a
	while (tmp->num < cur_b->num) 	// find first value in a that is bigger than b_front_val
	{
		count_ra++;
		tmp = tmp->next;
	}
	free(tmp);
	if (count_ra >= pd->a->cnt / 2 + 1)
		count_ra = count_ra * -1;	//is_rrab[0] = 1; // if count_ra is bigger than half of a, use rra instead of ra
	return (count_ra);
}

int	get_count_rb(t_pdeque	*pd, t_node *cur_b)//, int *is_rrab)
{
	int		count_rb;
	t_node	*tmp;

	count_rb = 0;
	if (cur_b == pd->b->front) 	// if the value is in the front, count_rb = 0
		return (count_rb);
	else // if the value is not in the front, count_rb = how many rb is needed before using pa
	{
		count_rb = 1;
		tmp = cur_b;
		while (tmp->prev != pd->b->front)	// calculate the distance between tmp and the front of b
		{
			count_rb++;
			tmp = tmp->prev;
		}
		free(tmp);
		if (count_rb >= pd->b->cnt / 2 + 1)
			count_rb = count_rb * -1;	//is_rrab[1] = 1; // if count_rb is bigger than half of b, use rrb instead of rb
	}
	return (count_rb);
}

void	execute_cmd(t_pdeque *pd, int *b_cmd_cnt, int *count_ra_arr)
{
	int		min_idx; // find min_idx
	int		i;

	i = 0;
	min_idx = 0;
	while (i < pd->b->cnt)
	{
		if (b_cmd_cnt[i] < b_cmd_cnt[min_idx])
			min_idx = i;
		i++;
	}
	// execute commands for the element in b that has the min_idx
	// 1. 먼저 ra/rra인지 rb/rrb인지 체크 (is_rrab[0] = 0: ra, 1: rra, is_rrab[1] = 0: rb, 1: rrb)
	// compare is_rrab[0] and is_rrab[1]
	if (is_rrab[0] == is_rrab[1]) // if is_rrab[0] == 0 and is_rrab[1] == 0, or is_rrab[0] == 1 and is_rrab[1] == 1 => rr or rrr
	{
		// 1-1. 둘 다 r 혹은 둘 다 rr이라면(즉, 0,0이거나 1,1이면) count_ra - count_rb 절대값만큼 rr 혹은 rrr 해줘야
		if (is_rrab[0] == 0)
		{
			if (count_ra > count_rb)
				while (count_ra - count_rb > 0)
				{
					command(pd, "rr");
					count_ra--;
				}
			else
				while (count_rb - count_ra > 0)
				{
					command(pd, "rrr");
					count_rb--;
				}
		}
		// 1-2. 만약 하나가 r이고 하나가 rr이면, count_ra, count_rb 만큼 각각 ra 혹은 rb 해줘야
		else
		{
			while (count_ra > 0)
			{
				command(pd, "ra");
				count_ra--;
			}
			while (count_rb > 0)
			{
				command(pd, "rb");
				count_rb--;
			}
		}
	}
	
	// 2-1. 둘 다 r 혹은 둘 다 rr이라면(즉, 0,0이거나 1,1이면) count_ra - count_rb 절대값만큼 rr 혹은 rrr 해줘야
	// 		그 후 둘 중 하나는 0이 되고, 나머지 하나는 남은 수만큼 ra 혹은 rb 해줘야
	// 2-2. 만약 하나가 r이고 하나가 rr이면, count_ra, count_rb 만큼 각각 ra 혹은 rb 해줘야
	// 두 경우 모두 다 끝나면 최종적으로 pa 실행


}
