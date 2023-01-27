/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:54:18 by dkham             #+#    #+#             */
/*   Updated: 2023/01/25 19:37:04 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		printparse(const char *format, va_list args);
int		ft_parse(const char *format, va_list ap);
int		ft_parse_type(const char *format, va_list ap);
int		print_c(int c);
int		print_s(char *s);
int		print_percent(void);
int		print_id(int d);
int		print_u(unsigned int u);
int		write_idu(long long number, int *count);
int		print_x(unsigned int x, const char format);
int		print_p(unsigned long long p);
int		write_hex(unsigned long long number, char *hex, int *count);

#endif