

ifndef BUILDDIR 
	export BUILDDIR=$(shell pwd)/build
endif

ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
else
#linux and mac here
	OS=$(shell uname -s)
	MD=mkdir -p
endif

ifeq ($(PREFIX),)
#install path
	PREFIX=/usr/local
endif


.PHONY: all lib obj clean test install uninstall

all: libann obj lib

windows: winobj winlib


libann:
	cd lib/libann; make

obj:
	$(MD) $(BUILDDIR)
	cd src; make obj

lib:
	$(MD) lib
	cd src; make lib

winobj:
	$(MD) $(BUILDDIR)
	cd src; make winobj

winlib: 
	$(MD) lib
	cd src; make winlib



test:
	cd test; make all

clean:
	#cd test; make clean
	-rm -v lib/libann.so
	-rm -v lib/libann.dll
	-rm -v lib/libann.dylib
	-rm -v build/*.o
	-rmdir -v build

install:
	cp -v include/ann.h $(PREFIX)/include

ifeq ($(OS),Linux)
	cp -v lib/libann.so $(PREFIX)/lib
	chmod 0775 $(PREFIX)/lib/libann.so
	ldconfig
else
	cp -v lib/libann.dylib $(PREFIX)/lib
	chmod 0775 $(PREFIX)/lib/libann.dylib
endif


uninstall:
	rm -v $(PREFIX)/include/ann.h
ifeq ($(OS),Linux)
	rm -v $(PREFIX)/lib/libann.so
	ldconfig
else
	rm -v $(PREFIX)/lib/libann.dylib
endif
