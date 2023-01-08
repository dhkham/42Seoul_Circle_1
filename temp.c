#include "ft_printf.h"
// #include "stdio.h"
// #include "ft_printf.c"
// #include "print.c"
// #include "ft_init_flags.c"
// #include "ft_atoi.c"
// #include "ft_strlen.c"
// #include "ft_isdigit.c"
// #include "ft_strchr.c"
// #include "ft_strncmp.c"

int main()
{
	// 그리고 기존 컴퓨터에서 다시 작업을 하려면, 변경된 내용을 아래와 같이 pull 해줘야 한다. 
	// git pull origin main
	// gcc temp.c ft_printf.c print.c ft_init_flags.c ./libft/*.c


	//53:  TEST(29, print(" %d %d %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));
	//int pf = printf   ("pf:%d %d %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	//int ft = ft_printf("ft:%d %d %d %d %d %d %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);


// - [OUTPUT] ft_printf("%08.3i", 8375)
// - [OUTPUT] ft_printf("%08.3i", -8473)
// - [OUTPUT] ft_printf("%8.3d", 8375)
// - [OUTPUT] ft_printf("%8.3d", -8473)
// - [OUTPUT] ft_printf("%08.3d", 8375)

	// - 는 width, precision에 포함되지 않는다
	// width: 최대 12 칸 찍는다
	// 공백은 width-precision만큼 찍는다(단 부호가 있을 경우 width-precision-1만큼 찍는다)
	// precision: 33포함 최소 x칸 찍는다(33 찍고 남은 칸은 0으로 패딩)
	// precision이 width보다 크면 precision만큼 33을 찍고 남은 칸은 0으로 패딩
	
	// 1. pass
	// int pf  = printf   ("pf:%-+12.7d\n", 33); 
	// int ft  = ft_printf("ft:%-+12.7d\n", 33); 
	// int pf  = printf   ("pf:%-+12.7d\n", -33); 
	// int ft  = ft_printf("ft:%-+12.7d\n", -33); 

	// 3. pass
	// int pf = printf("pf:%5i\n", 33);         // 총 5칸 찍기 / 33에 공백이나 부호 포함 2칸 찍기
	// int ft = ft_printf("ft:%5i\n", 33);      // 

	// int pf = printf("pf:%5i\n", -33);        // 총 5칸 찍기 / 33에 공백이나 부호 포함 2칸 찍기
	// int ft = ft_printf("ft:%5i\n", -33);     // 

	// int pf = printf("pf:%-5i\n", 33);        // 
	// int ft = ft_printf("ft:%-5i\n", 33);     //

	// int pf = printf("pf:%-5i\n", -33);       //
	// int ft = ft_printf("ft:%-5i\n", -33);    //



	// 4. no
	// int pf = printf   ("pf:%08.5i\n", 8375);
	// int ft = ft_printf("ft:%08.5i\n", 8375);

	// 2. no
	// int pf  = printf   ("pf:%05i\n", -43); 
	// int ft  = ft_printf("ft:%05i\n", -43);
	int pf  = printf   ("pf:%05i\n", 0); 
	int ft  = ft_printf("ft:%05i\n", 0); 
	printf("pf:%d | ft:%d", pf, ft);
}
