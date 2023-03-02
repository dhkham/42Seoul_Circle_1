/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 22:15:02 by dkham            ###   ########.fr       */
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

//ps_init(&ps)를 통해 ps가 가리키는 주소에 t_pdeque를 할당해준다.
void	ps_init(t_pdeque **ps)
{
	*ps = (t_pdeque *)malloc(sizeof(t_pdeque));
	(*ps)->a = (t_deque *)malloc(sizeof(t_deque)); // a는 t_deque를 가리키는 포인터가 아니기 때문에 에러 발생: struct에서 a를 포인터로 수정함
	(*ps)->b = (t_deque *)malloc(sizeof(t_deque));
	(*ps)->a->front = NULL;
	(*ps)->a->rear = NULL;
	(*ps)->a->cnt = 0;
	(*ps)->b->front = NULL;
	(*ps)->b->rear = NULL;
	(*ps)->b->cnt = 0;
}

// ps_parse: 입력받은 인자를 deque에 넣어주는 함수
void	ps_parse(t_pdeque **ps, int argc, char **argv)
{
	int		i;
	int		num;

	i = 0;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num == 0 && ft_strcmp(argv[i], "0") != 0)
			exit(-1);
		insert_rear((*ps)->a, num);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char		*cmd;
	t_pdeque	*ps; // * 붙는 거 맞는지 확인

	if (argc < 2)
		exit(-1);
	ps_init(&ps);
	ps_parse(&ps, argc - 1, argv + 1);
	push_swap(&ps);
	checker(&ps);
	exit(0);
}
