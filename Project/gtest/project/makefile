.PHONY: clean

all: main.o haizei/born.o 
	gcc main.o haizei/born.o -o ./bin/haizei
haizei/born.o: haizei/born.c haizei/gtest.h haizei/linklist.h
	gcc -c -I./ -o haizei/born.o haizei/born.c
main.o: main.c haizei/gtest.h
	gcc -c -I./ main.c
clean:
	rm -rf ./bin/haizei main.o haizei/born.o

