/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:23 by dkham             #+#    #+#             */
/*   Updated: 2023/03/02 22:12:23 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"

/*
t_node는 스택을 구성하는 노드를	의미한다.
t_deque은 스택을 구성하는 노드들의 시작과 끝을 가리키는 포인터 + 현 스택 노드의 수를 담고 있다.
t_pdeque은 스택 a, b를 가리키는 포인터를 가지고 있다. cnt는 필요한지 모르겠다.
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

typedef struct s_pdeque
{
	unsigned int	cnt; // 필요함???
	struct s_deque	*a; // 포인터로 수정!!!
	struct s_deque	*b;
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
int		command(t_pdeque *ps, char *cmd);
int		push(t_deque *from, t_deque *to);
int		swap(t_deque *st);
int		rotate(t_deque *st, enum e_rear rear);
int		is_rear(enum e_rear rear);
t_node	*dequeue(t_deque *st, enum e_rear rear);
void	enqueue(t_deque *st, enum e_rear rear, t_node *node);
t_node	*create_node(int num);
void	insert_front(t_deque *deque, int num);
void	insert_rear(t_deque *deque, int num);
int		delete_front(t_deque *deque);
int		delete_rear(t_deque *deque);
int		is_empty(t_deque *deque);
int		is_sorted(t_deque *deque);
void	ps_init(t_pdeque **ps)
void	ps_parse(t_pdeque **ps, int argc, char **argv)






#endif