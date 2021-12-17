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
	bigint *N = NULL;

	return N;
}

static bigint *bigint_alloc(digit x) {
	bigint *tmp = (bigint *)malloc(sizeof(bigint));

	if(tmp != NULL) {
		tmp->x    = x;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp;
}

static int bigint_delete(bigint *N) {
	bigint *HEAD = N;
	bigint *TAIL = N;
	if(N == NULL) {
		return 1;
	} else {
		if(N->next != HEAD)
			N->next->prev = N->prev;
		if(N->prev != TAIL)
			N->prev->next = N->next;
		free(N);
		return 0;
	}
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
	bigint **HEAD = *N;
	if(N != NULL) {
		do{
			head_delete(N);
		}while(*N != *HEAD && (*N)->x == 0 && (*N)->next != *HEAD);
	}
}

static bigint *last(bigint *N){
	bigint *HEAD = N;
	if(N != NULL){
		do{
			N = N->next;
		}while(N->next != HEAD);
	}
	return N;
}

static bigint *sum_pos(bigint *N1, bigint *N2) {
	bigint *N = NULL;
	bigint *TAIL_1 = N1->prev;
	bigint *TAIL_2 = N2->prev;
	if(SGN(N1) > 0 && SGN(N2) > 0) {
		int val = 0, car = 0;
		N1 = last(N1);
		N2 = last(N2);
		if(car != 0) {
			do{
				val = (N1 ? N1->x : 0) + (N2 ? N2->x : 0) + car;
				car = val / 10;
				val = val % 10;
				head_insert(&N,val);
				N1 = N1 ? N1->prev : NULL;
				N2 = N2 ? N2->prev : NULL;
			}while(N1 != TAIL_1 || N2 != TAIL_2 || car != 0);
		}
	}
	return N;
}

static int head_insert(bigint **N, digit x) {
	if(N == NULL) {
		return 1;
	}
	if(*N == NULL) {
		return N = bigint_alloc(x) == NULL;
	}

	bigint *tmp = bigint_alloc(x);

	if(tmp != NULL) {
		tmp->next = N;
		(*N)->prev = tmp;
		*N = tmp;
	}
	return tmp == NULL;
}

