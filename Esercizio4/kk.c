#include <stdio.h>

int fibonacci(int n){
    if(n <= 1){
        return 1;}
    else
        return (fibonacci(n-1) + fibonacci(n-2));
}

int main(void){
    pritnf("%d\n",fibonacci(10));
    return 0;
}