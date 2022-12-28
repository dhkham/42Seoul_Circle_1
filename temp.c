#include "stdio.h"
#include "string.h"
#include "ft_printf.h"

int main()
{
    // double num = 65.34;
    // printf("% f\n", num);
    // printf("% 05d\n", num);
    // printf("%+5d\n", num);
    // printf("%+-10d\n", 123);  // prints "+123      "
    // printf("hello%+011.9f%c\n", 3.14159265,'a');  // prints "hello+00003.142"
    // printf("%-10s %5d\n", "Hello", 123);  // prints "Hello      123"
    // printf("%6s", "hello");
    // char *str = "hello";
    // ft_strlen(str);

    // example of %p in printf
    int num = 10;
    printf("%20p", &num);

}
