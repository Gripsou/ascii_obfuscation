#include <stdio.h>

a(i)
    int i;
{
    printf("idx : %d --> %c\n",i,i);i<255?a(++i):++i;
}

main(){
    int i = 0; a(i);
}
