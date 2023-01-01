#include "ft_printf.h"
#include "stdio.h"

int main()
{
	// gcc temp.c ft_printf.c print.c ./libft/*.c
// 	int pf = printf   ("pf:%10.0d\n", 1);
// 	int ft = ft_printf("ft:%10.0d\n", 1);
// 	printf("pf:%d | ft:%d\n", pf, ft);

// 	int pf1 = printf   ("pf:%10.2d\n", 216);
// 	int ft1 = ft_printf("ft:%10.2d\n", 216);
// 	printf("pf:%d | ft:%d\n", pf1, ft1);

// 	int pf2 = printf   ("pf:%10.6d\n", -216);
// 	int ft2 = ft_printf("ft:%10.6d\n", -216);
// 	printf("pf:%d | ft:%d\n", pf2, ft2);

// 	int pf3 = printf   ("pf:%10.2d\n", 216);
// 	int ft3 = ft_printf("ft:%10.2d\n", 216);
// 	printf("pf:%d | ft:%d\n", pf3, ft3);

//printf("%x", 257);
	printf("%s", ft_itoa_base(156, 16));

// di 전반적인 구조에 대해 다시 생각해봐야...
	// int pf = printf   ("pf:%05i\n", 33); // => 해결 중
	// int ft = ft_printf("ft:%05i\n", 33);
	// printf("pf:%d | ft:%d\n", pf, ft);

// - [OUTPUT] ft_printf("%-7i", 33) => 메모리 문제??
// - [OUTPUT] ft_printf("%-7i", -14)
// - [OUTPUT] ft_printf("%-3i", 0)
// - [OUTPUT] ft_printf("%05i", 43) => 일단 해결
// - [OUTPUT] ft_printf("%07i", -54)
// - [OUTPUT] ft_printf("%03i", 0)
// - [OUTPUT] ft_printf("%8.5i", 34)
// - [OUTPUT] ft_printf("%8.5i", 0)
// - [OUTPUT] ft_printf("%8.3i", -8473)
// - [OUTPUT] ft_printf("%-8.5i", 34)
// - [OUTPUT] ft_printf("%-10.5i", -216)
// - [OUTPUT] ft_printf("%-8.5i", 0)
// - [OUTPUT] ft_printf("%-8.3i", 8375)
// - [OUTPUT] ft_printf("%-8.3i", -8473)
// - [OUTPUT] ft_printf("%08.5i", 34)
}
