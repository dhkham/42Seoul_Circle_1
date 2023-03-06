/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/03/06 20:32:53 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 구현 순서

1. 덱 구현하기		    (o)
2. 파싱 구현하기	     (o)
3. 커맨드 구현하기 		  (o)	
4. 정렬 로직 구현하기
	=> 피봇을 두개 잡아라

참고: ./push_swap 4 2 1 3 => 4가 front, 3이 rear => 1 2 3 4로 정렬해야 함
*/

#include "push_swap.h"
#include "stdio.h"

int	main(int argc, char **argv)
{
	t_pdeque	*pd;

	if (argc < 2)
		exit(-1);
	pd = pd_init();
	pd_parse(pd, argc, argv);
	
	// print all elements in deque a
	t_node *tmp = pd->a->front;
	while (tmp != NULL)
	{
		printf("a: %d\n", tmp->num);
		tmp = tmp->next;
	}

	command(pd, "pb");
	command(pd, "pb");
	command(pd, "pb");
	command(pd, "pb");
	command(pd, "pb"); // 4 3 2 5
	command(pd, "rrb");
	command(pd, "rrb");
	command(pd, "rb");

	t_node *tmp2 = pd->b->front;
	while (tmp2 != NULL)
	{
		printf("b: %d\n", tmp2->num);
		tmp2 = tmp2->next;
	}

	//push_swap(pd);
	//checker(&pd);
	exit(0);
}

t_pdeque	*pd_init(void)
{
	t_pdeque	*pd;

	pd = (t_pdeque *)malloc(sizeof(t_pdeque));
	if (pd == NULL)
		exit(1);
	pd->a = (t_deque *)malloc(sizeof(t_deque));
	if (pd->a == NULL)
	{
		free(pd);
		exit(1);
	}
	pd->b = (t_deque *)malloc(sizeof(t_deque));
	if (pd->b == NULL)
	{
		free(pd->a);
		free(pd);
		exit(1);
	}
	pd->a->front = NULL;
	pd->a->rear = NULL;
	pd->a->cnt = 0;
	pd->b->front = NULL;
	pd->b->rear = NULL;
	pd->b->cnt = 0;
	return (pd);
}

// pd_parse: 
// 여기서 Int 범위 확인 + "4 5 6" 같은 에러 처리 필요
// 중복수, 이미 정렬된 수 확인
void	pd_parse(t_pdeque *pd, int argc, char **argv)
{
	int		i;
	int		num;

	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num == 0 && ft_strncmp(argv[i], "0", 1) != 0)
			exit(-1);
		insert_rear(pd->a, num);
		i++;
	}
}
