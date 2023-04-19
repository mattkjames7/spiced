# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -Wextra -O3

IFLAGS=-I../lib/libann/include
LDFLAGS=-L../lib/libann/lib -lann

# Compiler
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

ifndef BUILDDIR
	BUILDDIR=../build
endif
BINDIR=$(BUILDDIR)/bin

OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIBFILE=libspiced.so
	CCo=g++ -c $(CFLAGS) -fopenmp $(IFLAGS)
	CC=g++ $(CFLAGS) -fopenmp $(IFLAGS)
else
	LIBFILE=libspiced.dylib
	LDFLAGS="-L/usr/local/opt/libomp/lib" -lomp
	CPPFLAGS="-I/usr/local/opt/libomp/include"
	CCo=g++ -Xpreprocessor -fopenmp -c $(CFLAGS) $(CPPFLAGS) $(IFLAGS)
	CC=g++ -Xpreprocessor -fopenmp $(CFLAGS) $(CPPFLAGS) $(IFLAGS)
endif

all: obj lib

obj:
	-mkdir -pv $(BINDIR)
ifeq ($(OS),Darwin)
	./macbins.sh "$(CCo)" $(BINDIR)

else
	#these are the average model parameters
	ld -r -b binary -o $(BINDIR)/mavh.o mavh.bin
	ld -r -b binary -o $(BINDIR)/mavcps.o mavcps.bin
	ld -r -b binary -o $(BINDIR)/mavcpt.o mavcpt.bin
	ld -r -b binary -o $(BINDIR)/ps.o ps.bin
	ld -r -b binary -o $(BINDIR)/pt.o pt.bin
	ld -r -b binary -o $(BINDIR)/prob.o prob.bin

	#these files contain the ANN weights, biases etc.
	ld -r -b binary -o $(BINDIR)/mavhann.o mavhann.bin
	ld -r -b binary -o $(BINDIR)/mavcpsann.o mavcpsann.bin
	ld -r -b binary -o $(BINDIR)/mavcptann.o mavcptann.bin
	ld -r -b binary -o $(BINDIR)/psann.o psann.bin
	ld -r -b binary -o $(BINDIR)/ptann.o ptann.bin
	ld -r -b binary -o $(BINDIR)/probann.o probann.bin

	#binary containing polynomals for mav transform
	ld -r -b binary -o $(BINDIR)/mavlambda.o mavlambda.bin
endif

	#source code
	$(CCo) annmodel.cc -o $(BUILDDIR)/annmodel.o
	$(CCo) annmavhmodel.cc -o $(BUILDDIR)/annmavhmodel.o
	$(CCo) annmavpsmodel.cc -o $(BUILDDIR)/annmavpsmodel.o
	$(CCo) annmavptmodel.cc -o $(BUILDDIR)/annmavptmodel.o
	$(CCo) annprobmodel.cc -o $(BUILDDIR)/annprobmodel.o
	$(CCo) annpsmodel.cc -o $(BUILDDIR)/annpsmodel.o
	$(CCo) annptmodel.cc -o $(BUILDDIR)/annptmodel.o
	$(CCo) avmodel.cc -o $(BUILDDIR)/avmodel.o
	$(CCo) avpsmodel.cc -o $(BUILDDIR)/avpsmodel.o
	$(CCo) avptmodel.cc -o $(BUILDDIR)/avptmodel.o
	$(CCo) avprobmodel.cc -o $(BUILDDIR)/avprobmodel.o
	$(CCo) avmavhmodel.cc -o $(BUILDDIR)/avmavhmodel.o
	$(CCo) avmavpsmodel.cc -o $(BUILDDIR)/avmavpsmodel.o
	$(CCo) avmavptmodel.cc -o $(BUILDDIR)/avmavptmodel.o
	$(CCo) mavtrans.cc -o $(BUILDDIR)/mavtrans.o
	$(CCo) polynomial.cc -o $(BUILDDIR)/polynomial.o
	$(CCo) rescale.cc -o $(BUILDDIR)/rescale.o
	$(CCo) reversearray.cc -o $(BUILDDIR)/reversearray.o
	$(CCo) libspiced.cc -o $(BUILDDIR)/libspiced.o

lib:
	$(CC) $(BINDIR)/*.o $(BUILDDIR)/*.o -fPIC -shared -o ../lib/$(LIBFILE) $(LDFLAGS)

clean:
	rm -v $(BUILDDIR)/*.o
