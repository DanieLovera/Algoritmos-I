CC=gcc
CFLAGS=-Wall -Werror -Wconversion -std=c99

azkaban: azkaban.c prision.c prision.h
	$(CC) $(CFLAGS) -o azkaban azkaban.c prision.c

prision.o: prision.c
	$(CC) $(CFLAGS) -o prision.o -c prision.c

clean:
	rm -f azkaban
	rm -f *.o

.PHONY: clean
