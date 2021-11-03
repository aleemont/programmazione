#include <stdio.h>
#include <stdlib.h>
#include "prime.c" 

int main(){
    int i;
    for(i=0; i<=6545; i++)
        printf("%d*succ_prime: %hu\n",i, succ_prime(0));
    return 0;
}