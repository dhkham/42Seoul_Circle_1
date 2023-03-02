/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:23 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 21:37:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"

/*
t_node는 스택을 구성하는 노드를	의미한다.
t_deque은 스택을 구성하는 노드들의 시작과 끝을 가리키는 포인터 + 노드의 수를 담고 있다.
t_pdeque은 스택 a, b를 가지고 있다.
*/

typedef struct s_node
{
	int				num; // 입력된 인자값 
	unsigned int	idx; // 입력된 전체 값에서의 순서
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	unsigned int	cnt; // 현재 스택의 노드 개수
	t_node			*front; 	//t_node	*node[2]; // 노드의 시작과 끝을 저장 => 대체 (rear, front)
	t_node			*rear;
}	t_deque;

//The s_deque struct contains additional information about the deque, 
//such as the current number of nodes (cnt), 
//as well as pointers to the first and last nodes in the deque 
//(node[0] and node[1], respectively). 
//These pointers can be used to access the individual nodes in the deque 
//and manipulate their contents or order.


//In the t_deque struct definition, the line t_node *node[2]; 
//declares an array called node that contains two pointers to t_node structs.

//This array is used to keep track of the beginning and end of the deque data structure
//represented by t_deque. The first element of the array (node[0])
//points to the bottom of the deque (i.e., the first node that was pushed onto the deque),
//while the second element (node[1]) points to the top of the deque 
//(i.e., the most recently pushed node).

typedef struct s_pdeque
{
	unsigned int	cnt; // 전체 스택의 사이즈
	struct s_deque	a;
	struct s_deque	b;
}	t_pdeque;

enum e_rear
{
	FRONT = 0,
	REAR = 1
};

// 1. The enum keyword is used to declare an enumeration.
// 2. The name of the enumeration is e_rear.
// 3. The enumeration has two values: FRONT and REAR.
// 4. The FRONT value has the value 0 and the REAR value has the value 1.

void	checker(t_pdeque *ps);
void	push_swap(t_pdeque *ps);




#endif