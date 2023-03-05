/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequefunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:27:13 by dkham             #+#    #+#             */
/*   Updated: 2023/03/05 19:32:24 by dkham            ###   ########.fr       */
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

//create_node: used in insert_front, insert_rear
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
void	insert_front(t_deque *deque, int num)
{
	t_node	*node;

	node = create_node(num);
	if (deque->front == NULL)// if the deque is empty
		deque->front = node; // set the deque to the new node
	else
	{
		// set the new node's next pointer to the current first node
		node->next = deque->front;
		// set the current first node's prev pointer to the new node
		deque->front->prev = node;
		// set the deque to the new node
		deque->front = node;
	}
	deque->cnt++;
}

//insert_rear
void	insert_rear(t_deque *deque, int num)
{
	t_node	*node;

	node = create_node(num);
	if (deque->rear == NULL)// if the deque is empty
	{
		deque->rear = node;// set the deque to the new node
		deque->front = node;
	}
	else
	{
		// set the new node's prev pointer to the current last node
		node->prev = deque->rear;
		// set the current last node's next pointer to the new node
		deque->rear->next = node;
		// set the deque to the new node
		deque->rear = node;
	}
	deque->cnt++;
}

//delete_front
int	delete_front(t_deque *deque)
{
	t_node	*temp;
	int		num;

	if (deque->front == NULL) // if the deque is empty
		return (-1);
	else
	{
		// point temp to the front of the deque
		temp = deque->front;
		// set the deque to the next node
		deque->front = deque->front->next;
		if (deque->front != NULL)	// if the deque is not empty
			deque->front->prev = NULL;	// set the new front node's prev pointer to NULL
		// save the value of the node we are deleting
		num = temp->num;
		// free the node
		free(temp);
		// decrease deque->cnt
		deque->cnt--;
		// return the value of the node we deleted
		return (num);
	}
}

//delete_rear
int	delete_rear(t_deque *deque)
{
	t_node	*temp;
	int		num;

	if (deque->rear == NULL)
		return (-1);
	else
	{
		temp = deque->rear;	// point temp to the rear of the deque
		deque->rear = deque->rear->prev; // set the deque to the previous node
		if (deque->rear != NULL) // if the deque is not empty
			// set the new rear node's next pointer to NULL
			deque->rear->next = NULL;
		num = temp->num;
		free(temp);
		deque->cnt--;
		return (num);
	}
}

//is_empty
int	is_empty(t_deque *deque)
{
	if (deque->front == NULL) // if the deque is empty
		return (1);
	else
		return (0);
}

//is_sorted
int	is_sorted(t_deque *deque)
{
	t_node	*temp;

	temp = deque->front;
	while (temp->next != NULL)
	{
		if (temp->num > temp->next->num)
			return (0);
		temp = temp->next;
	}
	return (1);
}
