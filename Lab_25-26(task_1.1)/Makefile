CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o functions.o 
	${CC} -o main main.o functions.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: functions.c functions.h
	${CC} ${CFLAGS} -c functions.c

clean: 
	rm -rf *.o main