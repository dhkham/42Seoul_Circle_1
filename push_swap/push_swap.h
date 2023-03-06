/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:23 by dkham             #+#    #+#             */
/*   Updated: 2023/03/06 20:16:50 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "stdlib.h"
# include "./libft/libft.h"

/*
t_node는 스택을 구성하는 노드를	의미한다.
t_deque은 스택을 구성하는 노드들의 시작과 끝을 가리키는 포인터 + 현 스택 노드의 수를 담고 있다.
t_pdeque은 스택 a, b를 가리키는 포인터를 가지고 있다. cnt는 필요한지 모르겠다.
*/

typedef struct s_node
{
	int				num;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_deque
{
	int		cnt;
	t_node	*front;
	t_node	*rear;
}	t_deque;

typedef struct s_pdeque
{
	struct s_deque	*a;
	struct s_deque	*b;
}	t_pdeque;

enum e_rear
{
	FRONT = 0,
	REAR = 1
};

t_pdeque	*pd_init(void);
void		pd_parse(t_pdeque *pd, int argc, char **argv);
void		push_swap(t_pdeque *pd);
void		bubblesort(int *tmp_arr, int a_len);
void		quick_sort(t_pdeque *pd, int pivot1, int pivot2);
void		sort_three(t_pdeque *pd);
t_node		*create_node(int num);
void		insert_front(t_deque *deque, int num);
void		insert_rear(t_deque *deque, int num);
int			delete_front(t_deque *deque, int *is_error);
int			delete_rear(t_deque *deque, int *is_error);
int			is_empty(t_deque *deque);
int			is_sorted(t_deque *deque);
int			command(t_pdeque *pd, char *cmd);
int			push(t_deque *from, t_deque *to);
int			swap(t_deque *deque);
int			rotate(t_deque *deque, enum e_rear is_rear);
void		checker(t_pdeque *pd);

#endif