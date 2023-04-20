

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

windows: libannwin winobj winlib

libann:
	cd lib/libann; make

libannwin:
	cd lib/libann; make windows

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
	cd lib/libann; make clean
	cd test; make clean
	-rm -v $(BUILDDIR)/bin/*.o
	-rmdir -v $(BUILDDIR)/bin/
	-rm -v $(BUILDDIR)/*.o
	-rmdir -v $(BUILDDIR)

install:
	cd lib/libann; make install

	cp -v include/spiced.h $(PREFIX)/include

ifeq ($(OS),Linux)
	cp -v lib/libspiced.so $(PREFIX)/lib
	chmod 0775 $(PREFIX)/lib/libspiced.so
	ldconfig
else
	cp -v lib/libspiced.dylib $(PREFIX)/lib
	chmod 0775 $(PREFIX)/lib/libspiced.dylib
endif


uninstall:
	cd lib/libann; make uninstall
	rm -v $(PREFIX)/include/spiced.h
ifeq ($(OS),Linux)
	rm -v $(PREFIX)/lib/libspiced.so
	ldconfig
else
	rm -v $(PREFIX)/lib/libspiced.dylib
endif
