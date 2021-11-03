/*
	21/09/2021
	
	Monticelli Alessandro - Primo anno Ingegneria e Scienze Informatiche - UniBO
	
	elaborato1.c
	
	Il seguente programma dichiara una variabile per ogni combinazione di specificatori e modificatori
	e stampa sul terminale: TIPO NOME VALORE MINIMO MASSIMO DIMENSIONE(in BYTE) per ogni variabile. 
*/
#include <stdio.h>
#include <limits.h> /*Libreria in cui sono definite le costanti 
					contenenti il massimo ed il minimo per i tipi interi*/
#include <float.h> /*Libreria in cui sono definite le costanti 
					contenenti il massimo ed il minimo per i tipi in virgola mobile*/

int main (void){
	/*	
		Dichiaro una variabile per ogni combinazione di 
		specificatori (int, char, float, double) e modificatori
		(short, long, signed, unsigned) 
	*/
	char c = 33;
	signed char sc = -33;
	unsigned char uc = 35;
	short s = 2;
	unsigned short us = 3;
	int i = 15;
	unsigned int ui = 42;
	long l = 25;
	unsigned long ul = 74;
	float f = 3.9;
	double d = 84.2;
	long double ld = 182.67;	
	/*
		Stampo sul terminale le informazioni per ogni variabile: 
	  	TIPO NOME VALORE MINIMO MASSIMO DIMENSIONE(in BYTE)
	 */  
	printf("TYPE: char\t\t NAME: c\t VALUE: %c\t MIN: %d\t\t\t MAX: %d\t\t\t BYTE: %d\n",c,CHAR_MIN,CHAR_MAX,(int)sizeof(c));
	printf("TYPE: signed char\t NAME: sc\t VALUE: %c\t\t MIN: %d\t\t\t MAX: %d\t\t\t BYTE: %d\n",sc,SCHAR_MIN,SCHAR_MAX,(int)sizeof(sc));
	printf("TYPE: unsigned char\t NAME: uc\t VALUE: %c\t MIN: %d\t\t\t\t MAX: %d\t\t\t BYTE: %d\n",uc,0,CHAR_MAX,(int)sizeof(uc));
	printf("TYPE: short\t\t NAME: s\t VALUE: %hi\t MIN: %hi\t\t\t MAX: %hi\t\t\t BYTE: %d\n",s,SHRT_MIN,SHRT_MAX,(int)sizeof(s));
	printf("TYPE: unsigned short\t NAME: us\t VALUE: %d\t MIN: %d\t\t\t\t MAX: %d\t\t\t BYTE: %d\n",us,0,USHRT_MAX,(int)sizeof(us));
	printf("TYPE: int\t\t NAME: i\t VALUE: %d\t MIN: %d\t\t MAX: %d\t\t BYTE: %d\n",i,INT_MIN,INT_MAX,(int)sizeof(i));
	printf("TYPE: unsigned int\t NAME: ui\t VALUE: %u\t MIN: %d\t\t\t\t MAX: %u\t\t BYTE: %d\n",c,0,UINT_MAX,(int)sizeof(ui));
	printf("TYPE: float\t\t NAME: f\t VALUE: %.3f\t MIN: %e\t\t MAX: %e\t\t BYTE: %d\n",f,FLT_MIN,FLT_MAX,(int)sizeof(f));
	printf("TYPE: long\t\t NAME: l\t VALUE: %ld\t MIN: %ld\t MAX: %ld\t BYTE: %d\n",l,LONG_MIN,LONG_MAX,(int)sizeof(l));
	printf("TYPE: unsigned long\t NAME: ul\t VALUE: %lu\t MIN: %d\t\t\t\t MAX: %lu\t BYTE: %d\n",ul,0,ULONG_MAX,(int)sizeof(ul));
	printf("TYPE: double\t\t NAME: d\t VALUE: %.3f\t MIN: %e\t\t MAX: %e\t\t BYTE: %d\n",d,DBL_MIN,DBL_MAX,(int)sizeof(d));
	printf("TYPE: long double\t NAME: ld\t VALUE: %.3Lf\t MIN: %Le\t\t MAX: %Le\t\t BYTE: %d\n",ld,LDBL_MIN,LDBL_MAX,(int)sizeof(ld));
		
	return 0;
}  

  
