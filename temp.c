#include "ft_printf.h"
#include "stdio.h"

int main()
{
	// 그리고 기존 컴퓨터에서 다시 작업을 하려면, 변경된 내용을 아래와 같이 pull 해줘야 한다. 
	// git pull origin main
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

// int pf = printf("pf:%7.4s\n", "hello");
// int ft = ft_printf("ft:%7.4s\n", "hello"); // . 이 나오면 무한루프 (해결?)

// printf("pf:%d || ft:%d\n", pf, ft);

// int pf = printf("pf:%7.7s%7.7s\n", "hello", "world");
// int ft = ft_printf("ft:%7.7s%7.7s\n", "hello", "world");

// printf("pf:%d || ft:%d\n", pf, ft);


// di 전반적인 구조에 대해 다시 생각해봐야...
	// int pf  = printf   ("pf:%12.7d\n", 33);    // pf:     0000033 pf:이후 총 12칸 찍기 / 33에 공백이나 부호 포함 7칸 찍기
	// int pf2 = printf   ("pf:%12.7d\n", -33);   // pf:    -0000033
	// int pf3 = printf   ("pf:%+12.7d\n", 33);   // pf:    +0000033

	int ft  = ft_printf("ft:%12.7d\n", 33);    // ft:     0000033
	int ft2 = ft_printf("ft:%12.7d\n", -33);   // ft:    -0000033
	int ft3 = ft_printf("ft:%+12.7d\n", 33);   // ft:    +0000033
	// int ft = ft_printf("ft:%05i\n", 33);
	// printf("pf:%d | ft:%d\n", pf, ft);
}
