/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:17:03 by dkham             #+#    #+#             */
/*   Updated: 2023/02/22 21:17:47 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void push_swap(struct s_pushswap *ps) { /* 정렬 로직 */ };
void checker(struct s_pushswap *ps)   { /* 체커 로직 */ };

int	main(int argc, char **argv)
{
	char 							*cmd;
	struct s_pushswap ps;

	if (argc < 2)
		exit(-1);
	ps_init(&ps);
	ps_parse(&ps, argc - 1, argv + 1);
	// push_swap(&ps);
	// checker(&ps);
	exit(0);
}