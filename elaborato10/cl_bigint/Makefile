CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89
 
all: mul 

cl_bigint.o: bigint.h cl_bigint.c
	gcc $(CFLAG) -c cl_bigint.c

mul: cl_bigint.o mul.c
	gcc $(CFLAG) cl_bigint.o mul.c -o mul

clean:
	rm -rf *.o mul 
