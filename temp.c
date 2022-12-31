#include "ft_printf.h"
#include "stdio.h"

int main()
{
	// gcc temp.c ft_printf.c print.c ./libft/*.c
	int pf = printf("pf:%7i\n", 33);
	int ft = ft_printf("ft:%7i\n", 33);
	printf("pf:%d | ft:%d\n", pf, ft);
}

// TEST(13, print(" %d ", -9));
// ft_printf("%7i", 33)
// ft_printf("%-7i", 33)
// ft_printf("%-7i", -14)
// ft_printf("%-3i", 0)
// ft_printf("%.6i", -3)