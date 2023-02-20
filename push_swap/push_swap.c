/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:13 by dkham             #+#    #+#             */
/*   Updated: 2023/02/20 22:22:10 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//deque: double ended queue
//queue: first in first out (dequeue: front 삭제, enqueue: rear 추가)
//stack: last in first out (pop: rear(=top) 삭제, push: rear(=top) 추가)

//deque는 양쪽에서 삭제, 추가 가능 (push front/rear, pop front/rear)
//=> insertFront, insertRear, deleteFront, deleteRear
//deque는 stack과 queue의 장점을 모두 가지고 있음

//ADT: 추상 자료형
//createDeque, deleteDeque, insertFront, insertRear, 
//deleteFront, deleteRear, isEmpty.
//double linked list로 구현

t_deque	*create_node(int data)
{
	t_deque	*node;

	node = (t_deque *)malloc(sizeof(t_deque));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	insert_front(t_deque **deque, int data)
{
	t_deque	*node;

	// create a new node
	node = create_node(data);

	// if the deque is empty
	if (*deque == NULL)
		// set the deque to the new node
		*deque = node;
	else
	{
		// otherwise, set the new node's next pointer to the current first node
		node->next = *deque;

		// set the current first node's prev pointer to the new node
		(*deque)->prev = node;

		// set the deque to the new node
		*deque = node;
	}
}

void	insert_rear(t_deque **deque, int data)
{
	t_deque	*node;
	t_deque	*temp;

	// create a new node
	node = create_node(data);
	// if deque is empty
	if (*deque == NULL)
		// add the new node to the front
		*deque = node;
	// otherwise
	else
	{
		// point temp to the front of the deque
		temp = *deque;
		// traverse the deque until we reach the end
		while (temp->next != NULL)
			temp = temp->next;
		// add the new node to the rear
		temp->next = node;
		// set the new node's prev pointer to the previous rear node
		node->prev = temp;
	}
}

int	delete_front(t_deque **deque)
{
	t_deque	*temp;		//temporary pointer
	int		data;		//data to be returned

	if (*deque == NULL)	//if deque is empty
		return (-1);	//error!
	temp = *deque;		//save the current front node to temp
	data = temp->data;	//save the data to be returned
	*deque = temp->next;	//make the next node the front node
	if (*deque != NULL)	//if the deque is not empty
		(*deque)->prev = NULL;	//make the prev pointer of the new front node NULL
	free(temp);		//free the old front node
	return (data);		//return the data
}

int	delete_rear(t_deque **deque)
{
	t_deque	*temp;		// 임시 노드
	int		data;		// 삭제할 데이터

	if (*deque == NULL)	// 덱이 비어있는 경우
		return (-1);
	temp = *deque;		// 삭제할 노드를 찾기 위해 임시 노드를 덱의 시작 노드로 지정
	while (temp->next != NULL)	// temp 노드가 덱의 마지막 노드가 될 때까지 반복
		temp = temp->next;
	data = temp->data;	// 삭제할 데이터 저장
	if (temp->prev != NULL)	// 삭제할 노드가 덱의 중간 노드인 경우
		temp->prev->next = NULL;	// 삭제할 노드의 이전 노드의 next를 NULL로 지정
	else	// 삭제할 노드가 덱의 시작 노드인 경우
		*deque = NULL;	// 덱의 시작 노드를 NULL로 지정
	free(temp);	// 삭제할 노드의 메모리 해제
	return (data);	// 삭제한 데이터 반환
}

int	is_empty(t_deque *deque)
{
	if (deque == NULL)
		return (1);
	return (0);
}
