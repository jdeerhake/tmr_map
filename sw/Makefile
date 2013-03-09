# Makefile for read jmr correction products program
# Linux
CC        = gcc -ansi -m32
LIBS      = -lm
CFLAGS    = -c -O3 -DNO_UNDER_SCORE -m32

# HP
#CC        = cc -Aa
#LIBS      = -lm
#CFLAGS    = -c  -DNO_UNDER_SCORE +O3 +Odataprefetch +DA2,0 +DS2.0

# Sun
#CC        = gcc -ansi
#LIBS      = -lm
#CFLAGS    = -c  -O

OBJ = readtmrrp.o r1cor.o

INC = r1cor.h

readtmrrp: $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o readtmrrp


readtmrrp.o: readtmrrp.c $(INC)
	$(CC) $(CFLAGS) readtmrrp.c

r1cor.o     : r1cor.c $(INC)
	$(CC) $(CFLAGS) r1cor.c

clean :
	/bin/rm -f *.o readtmrrp *~

