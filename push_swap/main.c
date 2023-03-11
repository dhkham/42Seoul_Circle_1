/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/03/11 21:52:37 by dkham            ###   ########.fr       */
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
	t_pdeque	*pd;

	if (argc < 2)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	pd = pd_init();
	pd_parse(pd, argc, argv);
	push_swap(pd);
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
	char	**split_arr;

	i = 1;
	while (i < argc)
	{
		// 2 "1 3" 6 5 같이 섞여 들어와도 받아줘야함
		if (ft_strchr(argv[i], ' '))
		{
			// printf("hello\n");
			// split_arr = ft_split(argv[i], ' ');
			// // print all elements of array
			// int j = 0;
			// while (split_arr[j])
			// {
			// 	printf("%s\n", split_arr[j]);
			// 	j++;
			// }
			// pd_parse(pd, argc, split_arr);
			// // pd_parse(pd, argc, split_arr);
			// // continue ;
		}
		num = ft_atoi(argv[i]);
		if (num == 0 && ft_strncmp(argv[i], "0", 1) != 0)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		check_duplicate(pd, num);
		insert_rear(pd->a, num);
		i++;
	}
}

void	check_duplicate(t_pdeque *pd, int num)
{
	t_node	*tmp;

	tmp = pd->a->front;
	while (tmp)
	{
		if (tmp->num == num)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		tmp = tmp->next;
	}
}
// 2 1 3 같은 형식이아닌 "2 1 3"처럼 하나의 문자열로 들어오는것도 받아줘야함
// 2 "1 3" 6 5 같이 섞여 들어와도 받아줘야함
// 음수가 들어와도 받아줘야함
// 숫자 이외의 문자가 들어올 시 에러 (o)
// 아무런 값이 들어오지 않을 시 에러 (o)
// 중복된 값이 들어올 시 에러 (o)