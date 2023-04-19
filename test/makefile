#includeflags
IFLAGS=-I../include -I../lib/libann/include

# Compiler

CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS) $(IFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS) $(IFLAGS)

OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LDFLAGS=-Wl,-rpath='$$ORIGIN/../lib' -L ../lib -lspiced -L../lib/libann/lib -lann
	#LDFLAGS= -L../lib/libspiced.so -L../lib/libann/lib -lann
	CFLAGS=-lm -std=c++17 -Wextra -O3 -fopenmp
	CCo=g++ -fPIC -c $(CFLAGS) $(IFLAGS)
	CC=g++ -fPIC $(CFLAGS) $(IFLAGS)
else
	LDFLAGS=-L../lib -lspiced -L/usr/local/opt/libomp/lib -lomp #-L../lib/libann/lib/libann.dylib
	CFLAGS=-lm -std=c++17 -Wextra -O3 "-I/usr/local/opt/libomp/include"
	CCo=g++ -Xpreprocessor -fopenmp -c $(CFLAGS) $(IFLAGS)
	CC=g++ -Xpreprocessor -fopenmp $(CFLAGS) $(IFLAGS)
endif

all:
	$(CCo) matdot.cc -o matdot.o
	$(CCo) matdot.cc -o matdot.o
	$(CCo) netfunc.cc -o netfunc.o
	$(CCo) probmodels.cc -o probmodels.o
	$(CCo) mavhmodels.cc -o mavhmodels.o
	$(CCo) mavpsmodels.cc -o mavpsmodels.o
	$(CCo) mavptmodels.cc -o  mavptmodels.o
	$(CCo) psmodels.cc -o psmodels.o
	$(CCo) ptmodels.cc -o ptmodels.o
	$(CCo) testmavtrans.cc -o testmavtrans.o
	$(CC) test.cc *.o -o test $(LDFLAGS)
	./test

clean:
	-rm -v *.o
	-rm -v test
