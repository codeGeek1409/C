#include<stdio.h>

int main(void){
    int a, b;
    puts("Enter in x,y: ");
    scanf("%d%*%d", &a, &b);
    printf("Value entered: %d %d", a, b);
    return 0;
}