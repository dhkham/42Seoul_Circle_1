/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/03/04 20:25:58 by dkham            ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	char		*cmd;
	t_pdeque	*pd; // * 붙는 거 맞는지 확인

	if (argc < 2)
		exit(-1);
	pd_init(&pd);
	pd_parse(&pd, argc, argv);
	push_swap(&pd);
	checker(&pd);
	exit(0);
}

//pd_init(&pd)를 통해 pd가 가리키는 주소에 t_pdeque를 할당해준다.
void	pd_init(t_pdeque **pd)
{
	*pd = (t_pdeque *)malloc(sizeof(t_pdeque));
	(*pd)->a = (t_deque *)malloc(sizeof(t_deque)); //a는 t_deque를 가리키는 포인터가 아니기 때문에 에러 발생: struct에서 a를 포인터로 수정함
	(*pd)->b = (t_deque *)malloc(sizeof(t_deque));
	(*pd)->a->front = NULL;
	(*pd)->a->rear = NULL; 
	(*pd)->a->cnt = 0;
	(*pd)->b->front = NULL;
	(*pd)->b->rear = NULL;
	(*pd)->b->cnt = 0;
}

// pd_parse: 입력받은 인자를 deque에 넣어주는 함수
void	pd_parse(t_pdeque **pd, int argc, char **argv)
{
	int		i;
	int		num;

	i = 1;
	while (i < argc)
	{
		/* convert the string to an int */
		num = ft_atoi(argv[i]);
		/* if the string is not a number, exit with error */
		//use ft_strncmp instead of ft_strcmp
		if (num == 0 && ft_strncmp(argv[i], "0", 1) != 0)
			exit(-1);
		/* insert the int at the end of the list */
		insert_rear((*pd)->a, num);
		i++;
	}
}
