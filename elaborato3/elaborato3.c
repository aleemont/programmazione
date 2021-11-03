/*NB: test x=0*/


#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

//#define EVAL //UNCOMMENT for testing but REMOVE from submission

int main() {
	unsigned int x;
	unsigned int res1=0, res2=0, res3=0;
	unsigned int cifra=0;
	unsigned int esp=0;
	unsigned int temp=0;

    //INPUT: x must be the input value, do not overwrite it 
	printf("Enter a positive integer: "); scanf("%u", &x);
    //calculate here
    temp = x;
	while(temp!=0){
		cifra = temp % 10;
		res1 = res1 * 10 + cifra;
		temp = temp / 10;
	}

	temp = x;
	for(esp = 0; temp != 0; esp++){
		temp = temp / 10;
	}
	if(x == 0)
		res2 = 10;
	else
		res2 = pow(10,esp) - x;
	temp = x;
	do{
		if(temp % 10 == 0)
			res3++;
		temp = temp / 10;
	}while(temp != 0);
    //do NOT add code after this point
    //OUTPUT
	printf("Actual result:\n");
	printf("%u %u %u\n", res1, res2, res3);
    
    //DON'T REMOVE from submittion
    #ifdef EVAL
        eval(x,res1, res2, res3);
    #endif
	return 0;
}
