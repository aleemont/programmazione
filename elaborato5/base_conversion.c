#include "base_conversion.h"
#include <stdio.h>
#include <math.h>

void base_conversion_rc(unsigned int n, unsigned int b) {
    if(b>1 && b <17){
        unsigned int r = 0;
    
        r = n % b;  /*Il resto della divisione tra n e b è pari all'ultima cifra del numero convertito in base b*/
            
        n /= b;
    
        if(n != 0)
            base_conversion_rc(n, b); /*Richiamo la funzione ricorsivamente*/
            
        printf("%X", r); /*Se r < 10 stampo r*/
    }
}

void base_conversion_it(unsigned int n, unsigned int b) {
    if(b>1 && b <17){
        unsigned int r = 0, k = 0, tmp = 0, i = 0;
    
        k = ceil((log(n+1)/log(b))); /*Numero di cifre di n convertito in base b*/
    
        while(k != 0){
            tmp = n;    /*Variabile temporanea per calcolare il resto della divisione*/
    
            for(i = 0; i < k; ++i){
                r = tmp % b;    /*Calcolo tutti i resti delle divisioni tra tmp e b per k volte*/
                tmp /= b;
            }
    
            printf("%X", r);
                
            --k; /*Decremento il numero di divisioni da effettuare*/
        }
    }
} 
