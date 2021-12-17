#include <stdlib.h>
#include "bigint.h"

#define SGN(N) ((N) == NULL ? 0 : ((N)->x < 0 ? -1 : 1))

bigint *mul(bigint *N1, bigint *N2);	/*Multiplies 2 bigint*/
static bigint *bigint_alloc(digit x);	/*Allocates one node with a digit inside*/
static int bigint_delete(bigint *N);	/*Deletes all the nodes of the list*/
static int head_insert(bigint **N, digit x);	/*Inserts one digit at the beginning of the lis*/
static int head_delete(bigint **N);	/*Deletes the first element*/
static void remove_leading_zeros(bigint **N);	/**/
static bigint *last(bigint *N);	/*Returns the last element of the list*/
static bigint *sum_pos(bigint *N1, bigint *N2);	/*Sums the elements of two lists*/
static int tail_insert(bigint **N, digit x);	/*Inserts one digit at the end of the list*/
static void add_zeros(bigint *N, unsigned int n);	/*Adds zeros for the sum of digits' multiplication results*/
static bigint *mul_digit_pos(bigint *N, digit x);	/**/
static bigint *mul_digit(bigint *N, digit x);	/*Multiplies 2 digits*/
static void negate(bigint *N);	/*Changes the sign of the first element of the list*/

bigint *mul(bigint *N1, bigint *N2) {
	int sgn1 = SGN(N1), sgn2 = SGN(N2);
	int n = 0;
	bigint *N = NULL, *tmp = NULL, *a = NULL, *b = NULL;
	if(sgn1 == 0 && sgn2 == 0)
	{
		return NULL;
	}

	if(sgn1 == -1)
		negate(N1);
	if(sgn2 == -1)
		negate(N2);

	tmp = last(N2);
	N = bigint_alloc(0);

	while(tmp != NULL)
	{
		a = mul_digit(N1, tmp->x);
		add_zeros(a, n++);
		b = sum_pos(N,a);
		bigint_delete(N);
		bigint_delete(a);
		N = b;
		tmp = tmp->prev;
	}

	if(sgn1 != sgn2)
		negate(N);
	
	return N;
}

static bigint *bigint_alloc(digit x) {
	bigint *tmp = (bigint *)malloc(sizeof(bigint));

	if(tmp != NULL) {
		tmp->x    = x;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return tmp;
}

static int bigint_delete(bigint *N) {
	if(N == NULL) {
		return 1;
	} else {
		if(N->next != NULL)
			N->next->prev = N->prev;
		if(N->prev != NULL)
			N->prev->next = N->next;
		free(N);
		return 0;
	}
}

static int head_insert(bigint **N, digit x) {
	if(N == NULL) {
		return 1;
	}
	
	if(*N == NULL) {
		return (*N = bigint_alloc(x)) == NULL;
	}

	bigint *tmp = bigint_alloc(x);

	if(tmp != NULL) {
		tmp->next = *N;
		(*N)->prev = tmp;
		*N = tmp;
	}
	return tmp == NULL;
	
}

static int head_delete(bigint **N) {
	if(N == NULL || *N == NULL) {
		return 1;
	} else {
		bigint *tmp = *N;

		*N = (*N)->next;
		return bigint_delete(tmp);
	}
}

static void remove_leading_zeros(bigint **N) {
	if(N != NULL) {
		while(*N != NULL && (*N)->x == 0 && (*N)->next != NULL)
			head_delete(N);
	}
}

static bigint *last(bigint *N){
	if(N != NULL){
		while(N->next != NULL)
			N = N->next;
	}
	return N;
}

static bigint *sum_pos(bigint *N1, bigint *N2) {
	bigint *N = NULL;
	if(SGN(N1) > 0 && SGN(N2) > 0) {
		int val = 0, car = 0;
		N1 = last(N1);
		N2 = last(N2);
		while(N1 != NULL || N2 != NULL || car != 0) {
			val = (N1 ? N1->x : 0) + (N2 ? N2->x : 0) + car;
			car = val / 10;
			val = val % 10;
			head_insert(&N,val);
			N1 = N1 ? N1->prev : NULL;
			N2 = N2 ? N2->prev : NULL;
		}
	}
	return N;
}

static int tail_insert(bigint **N, digit x) {
	if(N == NULL)
		return 1;
	if(*N == NULL)
		return head_insert(N,x);
	bigint *tmp = last(*N);
	tmp->next = bigint_alloc(x);
	if(tmp->next != NULL)
		tmp->next->prev = tmp;
	return tmp->next != NULL;
}

static void add_zeros(bigint *N, unsigned int n) {
	if(N != NULL && N->x != 0){
		int i = 0;
		for(i = 0; i < n; ++i)
			tail_insert(&N, 0);
	}
}

static bigint *mul_digit_pos(bigint *N, digit x) {
	bigint *X = NULL;
	int val = 0, car = 0;
	N = last(N);
	while(N != NULL || car != 0) {
		val = (N ? N->x : 0)*x + car;
		car = val / 10;
		val = val % 10;
		head_insert(&X,val);
		N = N ? N->prev : NULL;
	}
	return X;
}

static bigint *mul_digit(bigint *N, digit x) {
	bigint *X = NULL;
	if(N == NULL 
			||	x < -9 && x > 9)
		return NULL;
	if(x == 0)
		X = bigint_alloc(0);
	else {
		int sgn_n = SGN(N);
		X = mul_digit_pos(N,(x*sgn_n));
	}
	return X;
}

static void negate(bigint *N) {
	if(N != NULL)
		N->x *= -1;
}