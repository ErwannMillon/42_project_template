#define T "%s test"
#include <stdio.h>
void test(char *s)
{
    printf(s, "hhh");
}
int main(void)
{
    // printf(T, "hello");
    test(T);
}