array:
	gcc -c kdtree.c kdtree.h
	g++ -c test/array_test.cpp
	g++ -o array_test array_test.o kdtree.o
	- rm *.o *.gch

eigen:
	gcc -c kdtree.c kdtree.h
	g++ -c test/eigen_test.cpp
	g++ -o eigen_test eigen_test.o kdtree.o
	- rm *.o *.gch

static_lib:
	gcc -c kdtree.c -o kdtree.o
	ar rcs lib/libkdtree.a kdtree.o
	g++ test/array_test.cpp lib/libkdtree.a -o static_test
	- rm *.o

shared_lib:
	gcc -fPIC -shared kdtree.c -o lib/libkdtree.so
	g++ test/array_test.cpp lib/libkdtree.so -o shared_test

clear:
	- rm *_test