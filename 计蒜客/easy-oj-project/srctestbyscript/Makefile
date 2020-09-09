CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra

OBJS = oj.o run.o

.PHONY: clean

oj: $(OBJS)

oj.o: run.h

run.o: run.h

clean:
	$(RM) -- $(OBJS) oj 
