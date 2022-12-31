#include "ft_printf.h"
#include "stdio.h"

int main()
{
	// gcc temp.c ft_printf.c print.c ./libft/*.c
	int pf = printf("pf:%7i\n", -33);
	int ft = ft_printf("ft:%7i\n", -33);
	printf("pf:%d | ft:%d\n", pf, ft);
}

// 26:     TEST(2, print(" %d ", -1));
// 37:     TEST(13, print(" %d ", -9));
// 38:     TEST(14, print(" %d ", -10));
// 39:     TEST(15, print(" %d ", -11));
// 40:     TEST(16, print(" %d ", -14));
// 41:     TEST(17, print(" %d ", -15));
// 42:     TEST(18, print(" %d ", -16));
// 43:     TEST(19, print(" %d ", -99));

// - [OUTPUT] ft_printf("%7i", -14)
// - [OUTPUT] ft_printf("%-7i", 33)
// - [OUTPUT] ft_printf("%-7i", -14)
// - [OUTPUT] ft_printf("%-3i", 0)
// - [OUTPUT] ft_printf("%05i", 43)
// - [OUTPUT] ft_printf("%07i", -54)
// - [OUTPUT] ft_printf("%03i", 0)
// - [OUTPUT] ft_printf("%8.5i", 34)
// - [OUTPUT] ft_printf("%10.5i", -216)
// - [OUTPUT] ft_printf("%8.5i", 0)
// - [OUTPUT] ft_printf("%8.3i", -8473)
// - [OUTPUT] ft_printf("%-8.5i", 34)
// - [OUTPUT] ft_printf("%-10.5i", -216)
// - [OUTPUT] ft_printf("%-8.5i", 0)
// - [OUTPUT] ft_printf("%-8.3i", 8375)