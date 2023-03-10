/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:36:24 by dkham             #+#    #+#             */
/*   Updated: 2023/03/10 20:15:17 by dkham            ###   ########.fr       */
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
	// while (1)
	// {
	// 	sort_three(pd);
	// 	count_ras = (int *)malloc(sizeof(int) * pd->b->cnt);
	// 	count_rbs = (int *)malloc(sizeof(int) * pd->b->cnt);
	// 	get_count(pd, count_ras, count_rbs);
	// 	execute_cmd(pd, count_ras, count_rbs);
	// 	free(count_ras);
	// 	free(count_rbs);
	// 	if (pd->b->cnt == 0) // b원소 다 옮겼으면 루프 탈출
	// 		break ;
	// }
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
	int		ra_rb[2]; //[0]: ra 수, [1]: rb 수
	int		*cmd_cnt;
	int		min;
	int		min_idx;

	i = 0;
	cmd_cnt = (int *)malloc(sizeof(int) * pd->b->cnt); // min_idx 값 찾기 위해 count_ra/rra + count_rb/rrb 값 저장
	while (i < pd->b->cnt)
	{
		if (count_ras[i] < 0)
			ra_rb[0] = pd->a->cnt + count_ras[i]; // count_ra값이 음수: a 총 원소 수에 더해준 값만큼 rra해야함 (즉, count_rra로 바꿔 저장)
		else
			ra_rb[0] = count_ras[i]; 			  // count_ra값이 양수: count_ra번 ra해줘야함
		if (count_rbs[i] < 0)
			ra_rb[1] = pd->b->cnt + count_rbs[i]; // count_rb값이 음수: b 총 원소 수에 더해준 값만큼 rrb해야함 (즉, count_rrb로 바꿔 저장)
		else
			ra_rb[1] = count_rbs[i]; 		      // count_rb값이 양수: count_rb번 rb해줘야함
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
	// ra면 양수, rra면 음수 | rb면 양수, rrb면 음수

	// 둘 다 양수면(=ra,rb) 둘 중 하나가 0 될 때까지 rr
	// rr할 때마다 count_ra, count_rb 값도 같이 1 씩 감소시켜줘야
	// -> 둘 다 0이 되면 마지막으로 pa
	// -> 둘 중 하나 0이 되면 남은 count_ra/rb 수만큼 마저 ra/rb 실행
	if (count_ras[min_idx] >= 0 && count_rbs[min_idx] >= 0)
	{
		while (count_ras[min_idx] > 0 && count_rbs[min_idx] > 0) //2 / 1
		{
			command(pd, "rr");
			count_ras[min_idx]--; //1
			count_rbs[min_idx]--; //0
		}
		while (count_ras[min_idx] > 0)
		{
			command(pd, "ra");
			count_ras[min_idx]--;
		}
		while (count_rbs[min_idx] > 0)
		{
			command(pd, "rb");
			count_rbs[min_idx]--;
		}
	}
	// 둘 다 음수면 둘 중 하나가 0이 될 때 까지 rrr
	// rrr할 때마다 count_ra, count_rb 값도 같이 1 씩 증가시켜줘야
	// -> 둘 다 0이 되면 마지막으로 pa
	// -> 둘 중 하나 0이 되면 남은 count_ra/rb값 + a/b 총 원소 수만큼 rra/rrb 실행
	else if (count_ras[min_idx] < 0 && count_rbs[min_idx] < 0)
	{
		while (count_ras[min_idx] < 0 && count_rbs[min_idx] < 0)
		{
			command(pd, "rrr");
			count_ras[min_idx]++;
			count_rbs[min_idx]++;
		}
		count_ras[min_idx] = pd->a->cnt + count_ras[min_idx];
		count_rbs[min_idx] = pd->b->cnt + count_rbs[min_idx];
		while (count_ras[min_idx] > 0)
		{
			command(pd, "rra");
			count_ras[min_idx]--;
		}
		while (count_rbs[min_idx] > 0)
		{
			command(pd, "rrb");
			count_rbs[min_idx]--;
		}
	}
	// 부호 다르면 그냥 따로 count_ra/rb 수만큼 ra/rb 실행
	// 양수면 ra/rb, 음수면 rra/rrb
	else
	{
		if (count_ras[min_idx] > 0)
		{
			while (count_ras[min_idx] > 0)
			{
				command(pd, "ra");
				count_ras[min_idx]--;
			}
		}
		else
		{
			count_ras[min_idx] = pd->a->cnt + count_ras[min_idx];
			while (count_ras[min_idx] > 0)
			{
				command(pd, "rra");
				count_ras[min_idx]--;
			}
		}
		if (count_rbs[min_idx] > 0)
		{
			while (count_rbs[min_idx] > 0)
			{
				command(pd, "rb");
				count_rbs[min_idx]--;
			}
		}
		else
		{
			count_rbs[min_idx] = pd->b->cnt + count_rbs[min_idx];
			while (count_rbs[min_idx] > 0)
			{
				command(pd, "rrb");
				count_rbs[min_idx]--;
			}
		}
	}
	command(pd, "pa");
}

int	get_count_ra(t_pdeque	*pd, t_node *cur_b)
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

int	get_count_rb(t_pdeque	*pd, t_node *cur_b)
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
