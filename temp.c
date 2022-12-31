#include "ft_printf.h"
#include "stdio.h"

int main()
{
	// gcc temp.c ft_printf.c print.c ./libft/*.c
	int pf = printf   ("pf:%10.2d\n", -216);
	int ft = ft_printf("ft:%10.2d\n", -216);
	printf("pf:%d | ft:%d\n", pf, ft);

	int pf1 = printf   ("pf:%10.2d\n", 216);
	int ft1 = ft_printf("ft:%10.2d\n", 216);
	printf("pf:%d | ft:%d\n", pf1, ft1);

	int pf2 = printf   ("pf:%10.6d\n", -216);
	int ft2 = ft_printf("ft:%10.6d\n", -216);
	printf("pf:%d | ft:%d\n", pf2, ft2);

	int pf3 = printf   ("pf:%10.2d\n", 216);
	int ft3 = ft_printf("ft:%10.2d\n", 216);
	printf("pf:%d | ft:%d\n", pf3, ft3);
}
