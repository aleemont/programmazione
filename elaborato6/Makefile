CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89
  
all: pong pong_log

game.o: game.h game.c
	gcc $(CFLAG) -c game.c

display.o: display.h display.c
	gcc $(CFLAG) -c display.c

pong: game.h display.h game.o display.o main.c
	gcc $(CFLAG) display.o game.o main.c -o pong -lncurses

pong_log: game.h display.h game.o display.o main.c
	gcc $(CFLAG) -D REG display.o game.o main.c -o pong_log -lncurses

clean:
	rm -rf *.o pong pong_log