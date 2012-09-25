CC = cc
OPTION = -o
A_OPTION = -lm

dentaku_7	: dentaku_7.o
	${CC} -o $@ $@.c -lm
	rm -vf *.o
