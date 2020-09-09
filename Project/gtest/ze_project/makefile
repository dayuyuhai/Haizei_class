.PHONY: clean
all: main.o test/test.o
	g++ main.o test/test.o -o ./bin/haizei
main.o:
	g++ -c -I./ main.cpp
test/test.o: test/test.cc test/test.h
	g++ -c -I./ -o test/test.o test/test.cc
clean:
	rm -rf ./bin/haizei main.o test/test.o

