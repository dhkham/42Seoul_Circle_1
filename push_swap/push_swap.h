/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:23 by dkham             #+#    #+#             */
/*   Updated: 2023/02/22 22:21:03 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"

typedef struct s_stack_node
{
	int					num; //입력된 인자값 
	unsigned int		idx; //입력된 전체 값에서의 순서
	struct s_stack_node	*prev;
	struct s_stack_node	*next;
}	t_node;

typedef struct s_stack
{
	unsigned int	cnt; // 현재 스택의 개수
	t_node			*node[2]; // 노드의 시작과 끝을 저장
	//추가 (rear, front)
	t_node			*front;
	t_node			*rear;
}	t_stack;

struct s_pushswap
{
	unsigned int	cnt;// 전체 스택의 사이즈
	struct s_stack	a;
	struct s_stack	b;
};

enum e_rear
{
	FRONT = 0,
	REAR = 1
};

#endif