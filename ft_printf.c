/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:02:40 by dkham             #+#    #+#             */
/*   Updated: 2022/12/30 14:56:23 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// gcc ft_printf.c print.c ./libft/*.c

#include "stdio.h"
int main()
{
	// printf("hello%+010.3f\n", 3.14159265);  => "hello+00003.142"
	
	//printf("hello%c", 'a');
	//ft_printf("hello%c", 'a');
	//int num = 10;
    //printf("%c %c\n", 'a', 'b');
	//ft_printf("%c %c", 'a', 'b');
	printf("%%\n");
	ft_printf("%%\n");
	return (0);
}

int	ft_printf(const char *format, ...)
{
    va_list ap;
    int     count;

    va_start(ap, format);
    count = ft_vprintf(format, ap);
    va_end(ap);
    return (count);
}

int ft_vprintf(const char *format, va_list ap)
{
    int count;

    count = 0;
    while (*format) // loop thru format (= the " " part of printf, e.g., "hello%+010.3f\n")
    {     
        if (*format == '%')
        {
            format++; // move to next character after % sign
            count += ft_parse(&format, ap); // parse after % sign
        }
        else
        {
            write(1, format, 1); // if no % sign, just print out characters (e.g., hello)
            count++; // count number of characters printed
        }
        format++; // move to next character
    }
    return (count);
}

// %[flags(-, 0, ., #, ' ', +)][width][.precision]type(c, s, p, i, d, u, x, X, %)
int ft_parse(const char **format, va_list ap)
{
    t_flags flags;
    int     count;
    
    count = 0; //     printf("hello%+010.3f\n", 3.14159265);  => "hello+00003.142"
    ft_init_flags(&flags); // initialize flags struct
    while(ft_strchr("-0.# +123456789", **format)) // check for flags/width/precision after % sign
        ft_parse_flags(&flags, format); // parse flags
    if(ft_strchr("cspdiuxX%", **format))
        count += ft_parse_type(&flags, format, ap); // parse type
    return (count);
}

// check for flags after % sign (types are handled in ft_parse_type)
void ft_init_flags(t_flags *flags)
{
    flags->minus = 0; //- : left align
    flags->zero = 0; //0 : pad w/ 0
    flags->dot = 0; //. : for precision
    flags->hash = 0; //# : hexadecimal: 0x/0X, octal: 0
    //flags->space = 0; //' ' : space
    flags->plus = 0; //+ : sign (+, -)
    flags->width = 0; //width : minimum num of characters to be printed
    flags->precision = -1; //precision : num of digits printed after decimal point for floating point numbers
}

void ft_parse_flags(t_flags *flags, const char **format)
{
    if (**format == '-') // - : left align
        flags->minus = 1;
    else if (**format == '0') // 0 : pad w/ 0
        flags->zero = 1;
    else if (**format == '.') // . : for precision
        flags->dot = 1;
    else if (**format == '#') // # : hexadecimal: 0x/0X, octal: 0
        flags->hash = 1;
    //else if (**format == ' ') // ' ' : space
    //    flags->space = 1;
    else if (**format == '+') // + : sign (+ or -)
        flags->plus = 1;
    else if (ft_isdigit(**format)) // width : minimum num of characters to be printed
    {
        flags->width = (flags->width * 10) + ft_atoi(*format);
        while (ft_isdigit(**format))
            (*format)++;
        (*format)--; // points to last digit of width (before "." or type) => needed b/c while loop increments format at the end
    }
    
    // 문제 . 다음에 두자리 이상 올 때 위에 width 에서 걸려버림
    else if (**format == '.') // precision : num of digits printed after decimal point for floating point
    {
        flags->dot = 1;
        (*format)++; // move to next character
        flags->precision = 0;
        while (ft_isdigit(**format))
        {
            flags->precision = (flags->precision * 10) + ft_atoi(*format); // 1. (0*10)+3=3 // 2. (3*10) + 1=31
            (*format)++;
        }
        (*format)--; // points to last digit of precision (before type) => needed b/c while loop increments format at the end
    }
    (*format)++; // check next character
}

int ft_parse_type(t_flags *flags, const char **format, va_list ap)
{
    int count;

    count = 0;
    if (**format == 'c') // character
        count += print_c(flags, va_arg(ap, int));
    else if (**format == 's') // string
        count += print_s(flags, va_arg(ap, char *));
    else if (**format == 'p') // pointer
        count += print_p(flags, va_arg(ap, unsigned long long));
    else if (**format == 'i' || **format == 'd') // decimal integer
        count += print_di(flags, va_arg(ap, int));
    else if (**format == 'u') // unsigned decimal integer
        count += print_u(flags, va_arg(ap, unsigned int));
    else if (**format == 'x') // hexadecimal (lowercase)
        count += print_x(flags, va_arg(ap, unsigned int));
    else if (**format == 'X') // hexadecimal (uppercase)
        count += print_xx(flags, va_arg(ap, unsigned int));
    else if (**format == '%') // % character
        count += print_percent(flags);
    return (count);
}
