/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:13 by dkham             #+#    #+#             */
/*   Updated: 2023/02/22 22:17:00 by dkham            ###   ########.fr       */
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

//create_node
t_node	*create_node(int num)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->num = num;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

//insert_front
void	insert_front(t_stack *stack, int num)
{
	t_node	*node;

	node = create_node(num);
	// if the deque is empty
	if (stack->front == NULL)
		// set the deque to the new node
		stack->front = node;
	else
	{
		// set the new node's next pointer to the current first node
		node->next = stack->front;
		// set the current first node's prev pointer to the new node
		stack->front->prev = node;
		// set the deque to the new node
		stack->front = node;
	}
}

//insert_rear
void	insert_rear(t_stack *stack, int num)
{
	t_node	*node;
	t_node	*temp;

	// create a new node
	node = create_node(num);
	// if deque is empty
	if (stack->rear == NULL)
		// add the new node to the front
		stack->rear = node;
	else
	{
		// point temp to the front of the deque
		temp = stack->rear;
		// traverse the deque until we reach the end
		while (temp->next != NULL)
			temp = temp->next;
		// add the new node to the rear
		temp->next = node;
		node->prev = temp;
		stack->rear = node;
	}
}

//delete_front
int	delete_front(t_stack *stack)
{
	t_node	*temp;
	int		num;

	// if the deque is empty
	if (stack->front == NULL)
		return (-1);
	else
	{
		// point temp to the front of the deque
		temp = stack->front;
		// set the deque to the next node
		stack->front = stack->front->next;
		// if the deque is not empty
		if (stack->front != NULL)
			// set the new front node's prev pointer to NULL
			stack->front->prev = NULL;
		// save the value of the node we are deleting
		num = temp->num;
		// free the node
		free(temp);
		// return the value of the node we deleted
		return (num);
	}
}

//delete_rear
int	delete_rear(t_stack *stack)
{
	t_node	*temp;
	int		num;

	// if the deque is empty
	if (stack->rear == NULL)
		return (-1);
	else
	{
		// point temp to the rear of the deque
		temp = stack->rear;
		// set the deque to the previous node
		stack->rear = stack->rear->prev;
		// if the deque is not empty
		if (stack->rear != NULL)
			// set the new rear node's next pointer to NULL
			stack->rear->next = NULL;
		// save the value of the node we are deleting
		num = temp->num;
		// free the node
		free(temp);
		// return the value of the node we deleted
		return (num);
	}
}

//is_empty
int	is_empty(t_stack *stack)
{
	// if the deque is empty
	if (stack->front == NULL)
		return (1);
	else
		return (0);
}


// t_node	*create_node(int num)
// {
// 	t_node	*node;

// 	node = (t_node *)malloc(sizeof(t_node));
// 	node->num = num;
// 	node->prev = NULL;
// 	node->next = NULL;
// 	return (node);
// }

// void	insert_front(t_node **deque, int num)
// {
// 	t_node	*node;

// 	// create a new node
// 	node = create_node(num);

// 	// if the deque is empty
// 	if (*deque == NULL)
// 		// set the deque to the new node
// 		*deque = node;
// 	else
// 	{
// 		// otherwise, set the new node's next pointer to the current first node
// 		node->next = *deque;

// 		// set the current first node's prev pointer to the new node
// 		(*deque)->prev = node;

// 		// set the deque to the new node
// 		*deque = node;
// 	}
// }

// void	insert_rear(t_node **deque, int num)
// {
// 	t_node	*node;
// 	t_node	*temp;

// 	// create a new node
// 	node = create_node(num);
// 	// if deque is empty
// 	if (*deque == NULL)
// 		// add the new node to the front
// 		*deque = node;
// 	// otherwise
// 	else
// 	{
// 		// point temp to the front of the deque
// 		temp = *deque;
// 		// traverse the deque until we reach the end
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		// add the new node to the rear
// 		temp->next = node;
// 		// set the new node's prev pointer to the previous rear node
// 		node->prev = temp;
// 	}
// }

// int	delete_front(t_node **deque)
// {
// 	t_node	*temp;		//temporary pointer
// 	int		num;		//num to be returned

// 	if (*deque == NULL)	//if deque is empty
// 		return (-1);	//error!
// 	temp = *deque;		//save the current front node to temp
// 	num = temp->num;	//save the num to be returned
// 	*deque = temp->next;	//make the next node the front node
// 	if (*deque != NULL)	//if the deque is not empty
// 		(*deque)->prev = NULL;	//make the prev pointer of the new front node NULL
// 	free(temp);		//free the old front node
// 	return (num);		//return the num
// }

// int	delete_rear(t_node **deque)
// {
// 	t_node	*temp;		// 임시 노드
// 	int		num;		// 삭제할 데이터

// 	if (*deque == NULL)	// 덱이 비어있는 경우
// 		return (-1);
// 	temp = *deque;		// 삭제할 노드를 찾기 위해 임시 노드를 덱의 시작 노드로 지정
// 	while (temp->next != NULL)	// temp 노드가 덱의 마지막 노드가 될 때까지 반복
// 		temp = temp->next;
// 	num = temp->num;	// 삭제할 데이터 저장
// 	if (temp->prev != NULL)	// 삭제할 노드가 덱의 중간 노드인 경우
// 		temp->prev->next = NULL;	// 삭제할 노드의 이전 노드의 next를 NULL로 지정
// 	else	// 삭제할 노드가 덱의 시작 노드인 경우
// 		*deque = NULL;	// 덱의 시작 노드를 NULL로 지정
// 	free(temp);	// 삭제할 노드의 메모리 해제
// 	return (num);	// 삭제한 데이터 반환
// }

// int	is_empty(t_node *deque)
// {
// 	if (deque == NULL)
// 		return (1);
// 	return (0);
// }
