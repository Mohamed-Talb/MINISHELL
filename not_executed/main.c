#include <stdio.h>

int main()
{
    if (9223372036854775807 + 1 > 9223372036854775807)
        printf("can calculate in more than 64 bits\n");
    else
        printf("can't calculate\n");
}