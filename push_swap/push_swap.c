/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/09 22:25:06 by dkham            ###   ########.fr       */
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
	int		*count_ras;
	int		*count_rbs;

	while (pd->a->cnt > 3)
		command(pd, "pb");
	while (1)
	{
		sort_three(pd);
		count_ras = (int *)malloc(sizeof(int) * pd->b->cnt);
		count_rbs = (int *)malloc(sizeof(int) * pd->b->cnt);
		get_count(pd, count_ras, count_rbs);
		execute_cmd(pd, count_ras, count_rbs);
		free(count_ras);
		free(count_rbs);
		if (pd->b->cnt == 0) // b원소 다 옮겼으면 루프 탈출
			break ;
	}
}

void	get_count(t_pdeque *pd, int *count_ras, int *count_rbs)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = pd->b->front;
	while (tmp)
	{
		count_ras[i] = get_count_ra(pd, tmp->num); // b의 원소 하나하나에 대해 ra 수 계산(count_ra값이 음수: a 총 원소 수에 더해준 값만큼 rra해야함)
		count_rbs[i] = get_count_rb(pd, tmp->num); // b의 원소 하나하나에 대해 rb 수 계산(count_rb값이 음수: b 총 원소 수에 더해준 값만큼 rrb해야함)
		i++;
		tmp = tmp->next;
	}
}

void	execute_cmd(t_pdeque *pd, int *count_ras, int *count_rbs)
{
	// 먼저 count_ra, count_rb 값을 합한 것이 가장 작은 index를 찾는다.
	int		i;
	int		ra_rb[2];
	int		*cmd_cnt;
	int		min;
	int		min_idx;

	i = 0;
	cmd_cnt = (int *)malloc(sizeof(int) * pd->b->cnt);
	while (i < pd->b->cnt)
	{
		if (count_ras[i] < 0)
			ra_rb[0] = pd->a->cnt + count_ras[i];
		else
			ra_rb[0] = count_ras[i];
		if (count_rbs[i] < 0)
			ra_rb[1] = pd->b->cnt + count_rbs[i];
		else
			ra_rb[1] = count_rbs[i];
		cmd_cnt[i] = ra_rb[0] + ra_rb[1];
		i++;
	}
	// find minimum value's index in cmd_cnt
	min = cmd_cnt[0];
	min_idx = 0;
	i = 1;
	while (i < pd->b->cnt)
	{
		if (cmd_cnt[i] < min)
		{
			min = cmd_cnt[i];
			min_idx = i;
		}
		i++;
	}
	free(cmd_cnt);
	// execute commands for the element in b with minimum value's index
	// count_ras[min_idx], count_rbs[min_idx] 값에 따라 커맨드 실행
	// 둘 다 양수면 둘 중 하나가 0 이 될 때까지 rr (rr할 때마다 count_ra, count_rb 값도 같이 1 씩 감소시켜줘야)
	// -> 둘 다 0이 되면 그냥 pa
	// -> 둘 중 하나 0이 되면 남은 count_ra/rb 수만큼 ra/rb 실행

	// 둘 다 음수면 둘 중 하나가 0이 될 때 까지 rrr (rrr할 때마다 count_ra, count_rb 값도 같이 1 씩 증가시켜줘야),
	// -> 둘 다 0이 되면 그냥 pa
	// -> 둘 중 하나 0이 되면 남은 count_ra/rb값 + a/b 총 원소 수 만큼 ra/rb 실행
	
	// 부호 다르면 그냥 따로 count_ra/rb 수만큼 ra/rb 실행
	
	// 모든 경우에 최종적으로 pa 실행

}

// void	push_swap(t_pdeque *pd)
// {
// 	int		*b_cmd_cnt;
// 	int		*count_ra_arr;

// 	while (pd->a->cnt > 3)
// 		command(pd, "pb");
// 	sort_three(pd);
// 	while (1) // b->a로 다 옮길 때까지 무한 루프
// 	{
// 		b_cmd_cnt = (int *)malloc(sizeof(int) * pd->b->cnt); // b 원소 수만큼 커맨드 수 저장할 배열
// 		count_ra_arr = (int *)malloc(sizeof(int) * pd->b->cnt); // b 원소 수만큼 ra 수 저장할 배열
// 		get_cmd_cnt(pd, b_cmd_cnt, count_ra_arr); // b 모든 원소에 대해 커맨드 수 계산
// 		execute_cmd(pd, b_cmd_cnt, count_ra_arr); // 커맨드 수가 가장 작은 원소에 대해 커맨드 실행
// 		if (pd->b->cnt == 0) // 다 옮겼으면 루프 탈출
// 			break ;
// 		free(b_cmd_cnt);
// 		free(count_ra_arr);
// 	}
// }

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

// void	get_cmd_cnt(t_pdeque *pd, int *b_cmd_cnt, int *count_ra_arr)
// {
// 	int		count_ra;
// 	int		count_rb;
// 	int		i;
// 	int		*is_rrab;

// 	count_ra = 0;
// 	count_rb = 0;
// 	i = 0;
// 	is_rrab = (int *)malloc(sizeof(int) * pd->b->cnt * 2);
// 	while (i < pd->b->cnt)
// 	{
// 		count_ra = get_count_ra(pd, pd->b->front); // ra 몇 번 해야하는지 계산, rra인 경우는 음수로 리턴
// 		count_rb = get_count_rb(pd, pd->b->front); // rb 몇 번 해야하는지 계산, rrb인 경우는 음수로 리턴
// 		// from here
// 		// count_ra, count_rb is minus if rra/rrb is used!
// 		b_cmd_cnt[i] = count_ra + count_rb; // 확인
// 		count_ra_arr[i] = count_ra;
// 		i++;
// 	}
// }

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
