.PHONY: clean

all: main.o haizei/test.o 
	gcc main.o haizei/test.o -o ./bin/haizei
haizei/test.o: haizei/test.c haizei/gtest.h
	gcc -c -I./ -o haizei/test.o haizei/test.c
main.o: main.c
	gcc -c -I./ main.c
clean:
	rm -rf ./bin/haizei main.o haizei/test.o

#all: main.o haizei/test.o 
#	gcc main.o haizei/test.o -o ./bin/haizei
#haizei/test.o: haizei/test.c haizei/gtest.h
#	gcc -c -I./ -o haizei/test.o haizei/test.c
#main.o:
#	gcc -c -I./ main.c
#clean:
#	rm -rf ./bin/haizei main.o haizei/test.o


