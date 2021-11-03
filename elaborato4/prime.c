#include "prime.h"
#include <limits.h>

unsigned short int is_prime(unsigned short int n) {
    register unsigned short int i;
    /*Se n è < 2 non è mai primo*/
    if(n < 2)
       return 0;
    /*Un numero è primo se non ha altri divisori oltre 1 e se stesso, 
        controllo se è divisibile per un numero compreso tra 0 e n/2*/
    for(i = 2; i <= n >> 1 ; ++i){
        if(n % i == 0){
            return 0;
        }
    }
    return  1;
}
 
unsigned short int nth_prime(unsigned short int n) {
    register unsigned short int c = 0, num = 1, i;
    /*Ciclo per individuare l'n-esimo primo*/
    while(c <= n){
        /*Controllo per l'overflow*/
        if(num<USHRT_MAX)
            ++num;
        else
            return 0;
        /*Divido num per tutti i numeri tra 2 e num per trovare un divisore*/
        for(i=2; i<=num; ++i){
            if(num % i == 0)
                break;
        }
        /*Se il divisore trovato è uguale a num, allora num è primo, quindi incremento il contatore*/
        if(i == num)
            ++c;
        }
    return num;
}

static unsigned short int n = 1;
unsigned short int succ_prime(int reset){
    /*Se reset è diverso da 0 resetta la funzione*/
    if (reset) {
        n = 2;
        return n;
    }
    do {
        ++n;
        /*Controllo per overflow*/
        if (n == USHRT_MAX) {
            n = 1;
            return 0;
        }
    } while (!is_prime(n)); /*Incrementa n fino a quando non è primo*/
    return n;
}
 
static unsigned short int mcd(register unsigned short int m, register unsigned short int n) {
    /*Funzione per il calcolo del mcd*/
    while (m != n) {
        if (m > n) {
            m = m - n;
        }
        else {
            n = n - m; 
        }
    }
    return m;
}
 
unsigned short int co_prime(unsigned short int m, unsigned short int n) {
    /*Due nuomeri sono primi se il loro mcd è uguale a 1*/
    if(mcd(m,n) == 1)
        return 1;
    return 0;
}