#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bigint.h"

#define C2N(c) ((c)-'0')

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
	if(N == NULL) {
		return 1;
	} else {
		bigint *prv = N->prev, *nxt = N->next;
		nxt->prev = prv;
		prv->next = nxt;
		free(N);
		return 0;
	}
}

static int bigint_insert(bigint *N, digit x) {
	if(N == NULL) {
		return 1;
	} else {
		bigint *tmp = bigint_alloc(x), *nxt = N->next, *prv = N;
		if(tmp != NULL) {
			tmp->prev = prv;
			tmp->next = nxt;
			prv->next = tmp;
			nxt->prev = tmp;
		}
		return tmp == NULL;
	}
}

static int head_insert(bigint **N, digit x) {
	if(N == NULL)
		return 1;
	else if(*N == NULL)
		return (*N = bigint_alloc(x)) == NULL;
	else if (bigint_insert((*N)->prev,x) == 1)
		return 1;
	else
		return (*N = (*N)->prev) == NULL;
}

static int head_delete(bigint **N) {
	if(N == NULL || *N == NULL) {
		return 1;
	} else if (*N == (*N)->next) {
		free(*N);
		*N = NULL;
		return 0;
	} else {
		*N = (*N)->next;
		return bigint_delete((*N)->prev);
	}
}

static void remove_leading_zeros(bigint **N) {
	if(N != NULL && *N != NULL) {
		while((*N)->x == 0 && *N != (*N)->next)
			head_delete(N);
	}
}


static int well_formed_str(char *s) {
	if(s == NULL || *s == '\0') {
		return 0;
	} else {
		if(*s == '-') s++;
		if(*s == '\0')
			return 0;
		while(*s != '\0') {
			if(!isdigit(*s))
				return 0;
			s++;
		}
		return 1;
	}
}

static bigint *str2bigint_rec(char *s) {
	bigint *N = NULL;

	if(*s != '\0') {
		N = str2bigint_rec(s+1);
		head_insert(&N,C2N(*s));
	}
	return N;
}

static bigint *str2bigint(char *s) {
	bigint *N = NULL;

	if(well_formed_str(s)) {
		int sgn = 1;

		if(s[0]=='-') {
			sgn = -1;
			s++;
		}
		N = str2bigint_rec(s);
		remove_leading_zeros(&N);
		if(N != NULL && sgn == -1)
			N->x = -N->x;
	}

	return N;
}

void print(bigint *N) {
	if(N == NULL) {
		printf("NaN");
	} else {
		bigint *tmp = N;

		do {
			printf("%d",tmp->x);
			tmp = tmp->next;
		} while(tmp != N);
	}
}

int main(int argc, char *argv[]) {
	bigint *N1, *N2, *N;

	if(argc != 3) {
		fprintf(stderr,"Usage: mul <n1> <n2>\n");
		return 0;
	}
	
	N1 = str2bigint(argv[1]);
	N2 = str2bigint(argv[2]);
	N  = mul(N1,N2);
	
	print(N);printf("\n");
	
	return 0;
}
