CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89
 
all: mul 

dl_bigint.o: bigint.h dl_bigint.c
	gcc $(CFLAG) -c dl_bigint.c

mul: dl_bigint.o mul.c
	gcc $(CFLAG) dl_bigint.o mul.c -o mul

clean:
	rm -rf *.o mul 
