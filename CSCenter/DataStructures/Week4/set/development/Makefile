all: test

test: test.o set.o
	g++ -std=c++11 test.o set.o -o test
	
test.o: test.cpp set.h
	g++ -std=c++11 -c test.cpp
	
set.o: set.cpp set.h
	g++ -std=c++11 -c set.cpp
	
clean:
	rm -rf *.o test core vgcore.*
