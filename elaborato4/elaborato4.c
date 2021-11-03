#include <stdio.h>
#include <stdlib.h>
#include "prime.c" 

#define numFunctions 4
#define numTest 3


//main da usare in visual studio

int main() {
	int i,index, cont_err, cont_all;


	unsigned short int input[numTest][5] = {{281,3,3,16,17},
{353,46,46,1234,1235},
{359,1232,1232,29453,38333}};

	unsigned short int expout[numTest][4] = {{1,7,7,1},
{1,211,211,1},
{1,10039,10039,1}};



	int errors[numFunctions] = { 0,0,0,0};
	unsigned short int actual, expected;





	for (i = 0; i < numTest; i++) {
		printf("\nTest %hu: is_prime(%hu), nth_prime(%hu), %hu*succ_prime(0), co_prime(%hu,%hu) \n", i + 1, input[i][0],input[i][1],input[i][2],input[i][3],input[i][4]);

		expected = expout[i][0];
		actual = is_prime(input[i][0]);
		if (expected == actual)
			printf("is_prime ok: %hu\n", actual);
		else {
			printf("is_prime error: actual %hu - expected %hu\n", actual, expected);
			errors[0] += 1;
		}

		expected = expout[i][1];
		actual = nth_prime(input[i][1]);
		if (expected == actual)
			printf("nth_prime ok: %hu\n", actual);
		else {
			printf("nth_prime error: actual %hu - expected %hu\n", actual, expected);
			errors[1] += 1;
		}
		//Test succ_prime
        succ_prime(1);
		index=1;
		while (index < input[i][2]) {
			succ_prime(0);
			index++;
		};
		expected = expout[i][2];
		actual = succ_prime(0);

		if (expected == actual)
			printf("succ_prime ok: %hu\n", actual);
		else {
			printf("succ_prime error: actual %hu - expected %hu\n", actual, expected);
			errors[2] += 1;
		}

		expected = expout[i][3];
		actual = co_prime(input[i][3],input[i][4]);
		if (expected == actual)
			printf("co_prime ok: %hu\n", actual);
		else {
			printf("co_prime error: actual %hu - expected %hu\n", actual, expected);
			errors[3] += 1;
		}

	}


	cont_err = 0;
	cont_all = 0;
	for (i = 0; i < numFunctions; i++) {
		cont_err += (errors[i]>0);
		cont_all += errors[i];
	}




	printf("\nErrors %d/%d\n", cont_err, numFunctions);
	printf("\nTotal errors: ");
	for (i = 0; i < numFunctions; i++)  printf("\t %d", errors[i]);
	printf("\n");


	//printf("\nthe_grade_value=%f;num_tests_passed=%d;num_tests_failed=%d\n", 1.0*(numFunctions - cont_err) / numFunctions, numFunctions - cont_err, cont_err);
//	printf("<!--@test=%f;%d;%d;-->", 1.0*(numFunctions - cont_err) / numFunctions, numFunctions - cont_err, cont_err);


	return 1;
}
